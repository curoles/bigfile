/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#include "StdioFile.h"

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "Zlib.h"

using namespace file::stdio;

Instance::~Instance()
{
    close();
}

bool Instance::is_open_for_read_only()
{
    return ::fcntl(::fileno(file_), F_GETFL) & O_RDONLY;
}

//TODO use Open-file description locks, see https://gavv.github.io/blog/file-locks/
bool Instance::is_range_locked(int len)
{
    return 0 == ::lockf(::fileno(file_), F_TEST, len);
}

bool Instance::try_to_lock_range(int len)
{
    return 0 == ::lockf(::fileno(file_), F_TLOCK, len);
}

bool Instance::unlock_range(int len)
{
    return 0 == ::lockf(::fileno(file_), F_ULOCK, len);
}

bool file::stdio::zdeflate(const fs::path& src_path, const fs::path& dest_path)
{
    auto src = file::stdio::open(src_path, "r");
    if (!src.is_open()) return false;

    auto dest = file::stdio::open(dest_path, "w");
    if (!dest.is_open()) return false;

    return file::zlib::zdeflate(src.getFILE(), dest.getFILE());
}

bool file::stdio::zinflate(const fs::path& src_path, const fs::path& dest_path)
{
    auto src = file::stdio::open(src_path, "r");
    if (!src.is_open()) return false;

    auto dest = file::stdio::open(dest_path, "w");
    if (!dest.is_open()) return false;

    return file::zlib::zinflate(src.getFILE(), dest.getFILE());
}
