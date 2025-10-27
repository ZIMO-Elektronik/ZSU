// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at https://mozilla.org/MPL/2.0/.

/// Read ZSU file
///
/// \file   zsu/zsu.hpp
/// \author Vincent Hamp
/// \date   26/10/2023

#pragma once

#include <filesystem>
#include "file.hpp"

namespace zsu {

/// Read ZSU file
///
/// Throws std::filesystem::filesystem_error on invalid paths.
///
/// \param  path  Path to ZSU file
/// \return ZSU file
File read(std::filesystem::path path);

} // namespace zsu
