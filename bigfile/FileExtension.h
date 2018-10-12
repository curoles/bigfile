/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#pragma once

#include <string>
#include <tuple>
#include "FileSystem.h"

namespace file::ext {

auto isTextExt(const std::string& extname) -> std::tuple<bool,bool/*err*/>;


static inline
auto isTextFile(const fs::path& path) -> std::tuple<bool,bool/*err*/>
{
   return isTextExt(path.extension());
}

} // namespace file::ext
