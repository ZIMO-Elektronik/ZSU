// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

///
///
/// \file   zsu/file.hpp
/// \author Vincent Hamp
/// \date   26/10/2023

#pragma once

#include <vector>
#include "firmware.hpp"
#include "header.hpp"

namespace zsu {

struct File {
  Header header;
  std::vector<Firmware> firmwares;
};

}  // namespace zsu