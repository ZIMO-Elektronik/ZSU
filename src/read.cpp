// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Read ZSU file
///
/// \file   read.cpp
/// \author Vincent Hamp
/// \date   26/10/2023

#include <algorithm>
#include <charconv>
#include <fstream>
#include <ranges>
#include "zsu.hpp"

namespace zsu {

File read(std::filesystem::path path) {
  if (!exists(path))
    throw std::filesystem::filesystem_error(
      "ZSU file does not exist",
      path,
      std::make_error_code(std::errc::file_exists));

  std::ifstream stream{path, std::ios::binary};
  std::string const chunk{std::istreambuf_iterator<char>{stream},
                          std::istreambuf_iterator<char>{}};

  auto header{chunk | std::views::take_while([](char c) { return c != ':'; }) |
              std::views::split(';')};

  File file;

  // Get file identifier and version
  auto info{header | std::views::take(1)};
  auto str{info.front()};
  std::ranges::copy_n(begin(str), 2, std::back_inserter(file.info.id));
  file.info.version = str[3uz] - '0';

  //
  auto firmwares{header | std::views::drop(1)};
  std::ranges::transform(
    firmwares, std::back_inserter(file.firmwares), [&](auto&& block) {
      auto entries{block | std::views::split('\t')};
      auto first{begin(entries)};
      auto const last{end(entries)};
      Firmware fw;

      // ID
      str = *first++;
      std::from_chars(data(str), data(str) + size(str), fw.id);

      // Binary data start address
      str = *first++;
      int start;
      std::from_chars(data(str), data(str) + size(str), start);

      // Binary data length
      str = *first++;
      int length;
      std::from_chars(data(str), data(str) + size(str), length);

      // Name
      std::ranges::copy(*first++, std::back_inserter(fw.name));

      // Major version
      std::ranges::copy(*first++, std::back_inserter(fw.major_version));

      // Minor version
      std::ranges::copy(*first++, std::back_inserter(fw.minor_version));

      // Type
      str = *first++;
      std::from_chars(data(str), data(str) + size(str), fw.type);

      // Bootloader
      if (first != last) {
        str = *first++;
        int bl_type;
        std::from_chars(data(str), data(str) + size(str), bl_type);
        fw.bl_type = bl_type;
      }

      // IV
      if (first != last) {
        str = *first++;
        uint64_t iv;
        std::from_chars(data(str), data(str) + size(str), iv);
        fw.iv = {static_cast<uint8_t>(iv >> 56u),
                 static_cast<uint8_t>(iv >> 48u),
                 static_cast<uint8_t>(iv >> 40u),
                 static_cast<uint8_t>(iv >> 32u),
                 static_cast<uint8_t>(iv >> 24u),
                 static_cast<uint8_t>(iv >> 16u),
                 static_cast<uint8_t>(iv >> 8u),
                 static_cast<uint8_t>(iv >> 0u)};
      }

      // Bin
      if (fw.type < 3) length -= 2;
      fw.bin.reserve(static_cast<size_t>(length));
      std::ranges::copy_n(cbegin(chunk) + start + 1,  // Legacy bug
                          length,
                          begin(fw.bin));
      fw.bin.resize(static_cast<size_t>(length));

      return fw;
    });

  return file;
}

}  // namespace zsu