// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Salsa20 initialization vector
///
/// \file   zsu/iv.hpp
/// \author Vincent Hamp
/// \date   26/10/2023

#pragma once

#include <array>
#include <cstdint>

namespace zsu {

/// Salsa20 initialization vector
using IV = std::array<uint8_t, 8uz>;

} // namespace zsu
