/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#pragma once

#include <string>

namespace file {

enum class error
{
    OK = 0,
    NONE = OK,
    ERROR,
    CHECK_ERRNO,
    CHECK_FERROR,
    CHECK_STD_ERR_CODE,
    ALREADY_OPEN,
    ALREADY_EXISTS
};

static inline
auto is_err(file::error err) { return err != file::error::OK; }

static inline
auto operator!(file::error err) { return err == file::error::NONE;}

auto errmsg(file::error err, int ferr = 0) -> std::string;

} // namespace file
