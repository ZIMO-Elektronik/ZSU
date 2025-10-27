// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// ZSU file
///
/// \file   zsu/file.hpp
/// \author Vincent Hamp
/// \date   26/10/2023

#pragma once

#include <vector>
#include "firmware.hpp"
#include "info.hpp"

namespace zsu {

/// ZSU file consisting of info and firmwares
struct File {
  Info info{};
  std::vector<Firmware> firmwares;
};

} // namespace zsu
