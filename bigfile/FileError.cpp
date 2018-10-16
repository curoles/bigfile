/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#include "FileError.h"

#include <cstring>
#include <system_error>
	
auto file::errmsg(file::error err, int ferr) -> std::string
{
    switch (err) {
    case file::error::NONE: return "no error";
    case file::error::CHECK_ERRNO: return "check errno";
    case file::error::CHECK_FERROR: return std::strerror(ferr);
    case file::error::CHECK_STD_ERR_CODE:
        return std::error_code(ferr, std::system_category()).message();
    case file::error::ALREADY_OPEN: return "File already open";
    case file::error::ALREADY_EXISTS: return "File already exists";
    case file::error::CAN_NOT_CREATE: return "Can't create";
    case file::error::CAN_NOT_OPEN: return "Can't open";
    case file::error::CAN_NOT_GET_LOCK: return "Can't get lock";
    default: break;
    }

    return "error " + std::to_string((int)err);
};

