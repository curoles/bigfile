/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#pragma once

#include "FileSystem.h"

namespace file {

struct Info
{
    bool isText; // text or binary
    bool isBig;
    bool isJournal; // append+read
    //text encoding
    //zipped
    //encrypted
};

namespace info {

auto create_xattr(
    const fs::path& path,
    const std::string& name, const std::string& value) -> bool;

auto replace_xattr(
    const fs::path& path,
    const std::string& name, const std::string& value) -> bool;

auto create_or_replace_xattr(
    const fs::path& path,
    const std::string& name, const std::string& value) -> bool;

auto get_xattr(
    const fs::path& path,
    const std::string& name) -> std::tuple<std::string,bool/*err*/,std::string/*errmsg*/>;

} // namespace info
} // namespace file
