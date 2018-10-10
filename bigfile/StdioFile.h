/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#pragma once

#include <string>
#include <cstdio>

namespace file::stdio {

class Instance
{
    FILE* file_ = nullptr;
public:
   ~Instance() {
        close();
    }

    bool isOpen() const {
        return file_ != nullptr;
    }

    void close() {
        if (isOpen()) {
            ::fclose(file_);
            file_ = nullptr;
        }
    }

    bool open(const std::string& path, const std::string& mode) {
        if (isOpen()) return false;
        file_ = ::fopen(path.c_str(), mode.c_str());
        return isOpen();
    }

    bool write(const std::string& str) {
        int ret = ::fputs(str.c_str(), file_);
        return ret > 0;
    }
};

static inline
auto open(const std::string& fname, const std::string& mode) -> file::stdio::Instance
{
    file::stdio::Instance file;
    file.open(fname, mode);

    return file;
}

} // namespace file::stdio
