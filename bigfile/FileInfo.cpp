/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#include "FileInfo.h"

#include <sys/types.h>
#include <sys/xattr.h>
#include <errno.h>

static
bool
file_set_xattr(
    const fs::path& path,
    const std::string& name,
    const std::string& value,
    int flags
)
{
    int ret = ::setxattr(path.c_str(), name.c_str(), value.c_str(), value.size(), flags);

    if (ret == 0 ) return true;
#if 0
    switch (errno) {
    case EDQUOT: errmsg = "insufficient disk space"; break;
    case EEXIST: errmsg = "XATTR_CREATE was specified, and the attribute exists already"; break;
    case ENOATTR: errmsg = "XATTR_REPLACE was specified, and the attribute does not exist"; break;
       ENOSPC "insufficient disk space"
       ENOTSUP "The namespace prefix of name is not valid"
       ENOTSUP "Extended attributes are not supported by the filesystem, or are disabled"
       EPERM  "The file is marked immutable or append-only"
    }
#endif
    return false;
}

auto file::info::create_xattr(
    const fs::path& path,
    const std::string& name, const std::string& value) -> bool
{
    return file_set_xattr(path, name, value, XATTR_CREATE);
}

auto file::info::replace_xattr(
    const fs::path& path,
    const std::string& name, const std::string& value) -> bool
{
    return file_set_xattr(path, name, value, XATTR_REPLACE);
}

auto file::info::create_or_replace_xattr(
    const fs::path& path,
    const std::string& name, const std::string& value) -> bool
{
    return file_set_xattr(path, name, value, 0);
}

auto file::info::get_xattr(
    const fs::path& path,
    const std::string& name) -> std::tuple<std::string,bool/*err*/,std::string/*errmsg*/>
{
    return std::make_tuple("",true,"");//FIXME
}

