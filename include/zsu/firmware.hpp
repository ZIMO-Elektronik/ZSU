// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Firmware data
///
/// \file   zsu/firmware.hpp
/// \author Vincent Hamp
/// \date   26/10/2023

#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>
#include "iv.hpp"

namespace zsu {

/// Firmware data (and meta data)
struct Firmware {
  uint32_t id{};               // Decoder ID
  std::string name;            // Decoder name
  std::string major_version;   // Major version
  std::string minor_version;   // Minor version
  int type{};                  // Type
  std::optional<int> bl_type;  // Optional bootloader type
  std::optional<IV> iv;        // Optional Salsa20 initialization vector
  std::vector<uint8_t> bin;    // Binary data
};

}  // namespace zsu