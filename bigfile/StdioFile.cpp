/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#include "StdioFile.h"

#include "Zlib.h"

using namespace file::stdio;

Instance::~Instance()
{
    close();
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
