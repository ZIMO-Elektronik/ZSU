// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

///
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

namespace zsu {

struct Firmware {
  std::array<uint8_t, 4uz> id;
  std::string name;
  std::string major_version;
  std::string minor_version;
  int type;
  std::optional<int> bootloader;
  std::optional<std::array<uint8_t, 8uz>> iv;
  std::vector<uint8_t> bin;
};

}  // namespace zsu