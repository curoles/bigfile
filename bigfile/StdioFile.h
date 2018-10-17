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
#include <functional>
#include <iostream>
#include <fstream>
#include <memory>
#include <cstdio>
#include <cerrno>
#include <cstring>

#include "FileSystem.h"
#include "FileError.h"

namespace file::stdio {

static inline
void read_all_with_fgetc(FILE* fp, std::string& s, size_t max_size)
{
    size_t size = 0;
    int c; while ((c = ::fgetc(fp)) != EOF && size < max_size) {
        s += (char)c;
        ++size;
    }
}

static inline
void read_all_with_fread(FILE* fp, std::string& s, size_t max_size)
{
    char buf[16*1024]; size_t num_bytes_received; size_t size = 0;
    while ((num_bytes_received = ::fread(buf, 1, sizeof(buf), fp)) != 0
            && size < max_size)
    {
        s.append(buf, num_bytes_received);
        size += num_bytes_received;
    }
}

class Instance
{
    FILE* file_ = nullptr;
public:
    Instance():file_{nullptr}{}
   ~Instance();
    Instance(Instance&&) = default;
    Instance(const Instance&) = delete;

    Instance& operator=(Instance&&) = delete;
    Instance& operator=(const Instance&) = delete;

    FILE* getFILE() {return file_;}

    bool is_open() {
        return file_ != nullptr;
    }

    void close() {
        if (is_open()) {
            ::fclose(file_);
            file_ = nullptr;
        }
    }

    bool open(const std::string& path, const std::string& mode) {
        if (is_open()) return false;
        file_ = ::fopen(path.c_str(), mode.c_str());
        return is_open();
    }

    bool write(const std::string& str, size_t len = 0) {
        size_t size = (len == 0)? str.size() : std::min(str.size(), len);
        size_t num_written_elements = ::fwrite(str.c_str(), 1, size, file_);
        return num_written_elements == size;
    }

    void set_at_beginning() {
        ::rewind(file_); //::fseek(file_, 0, SEEK_SET);
    }

    std::tuple<std::string,file::error,int>
    read_as_string(bool from_beginning = true,
                   size_t max_size = 128*1024*1024,
                   void (*reader)(FILE*,std::string&,size_t) = read_all_with_fread)
    {
        std::string s;

        if (from_beginning) set_at_beginning();
        reader(file_, s, max_size);

        if (::ferror(file_)) {
            return std::make_tuple(s, file::error::CHECK_FERROR, std::ferror(file_));
        }

        return std::make_tuple(s, file::error::NONE, 0);
    }

    void for_each_char(std::function<bool(char)> f)
    {
        int c; while ((c = ::fgetc(file_)) != EOF && f((char)c)) { /*keep running*/ }
    }

    bool is_open_for_read_only();

    bool is_range_locked(int len = 0 /*0 means infinity*/);
    bool try_to_lock_range(int len = 0);
    bool unlock_range(int len = 0);

    size_t file_size();
};

static inline
auto open(const std::string& fname, const std::string& mode) -> file::stdio::Instance
{
    file::stdio::Instance file;
    file.open(fname, mode);

    return file;
}

static inline
size_t count_lines(file::stdio::Instance& file)
{
    size_t count{0};
    auto line_counter = [&count](char c){if (c == '\n') count++; return /*continue*/true;};
    file.for_each_char(line_counter);
    return count;
}

#ifdef __GNUC__
#include <ext/stdio_filebuf.h>

// User is responsible returned buffer does NOT outlive the file.
//
// Example:
//    auto streambuf = file::stdio::make_streambuf<char>(f);
//    std::istream instream(streambuf.get());
//
//    for (std::string line; std::getline(instream, line); ) {
//        std::cout << line << std::endl;
//    }
//
template<typename T>
std::unique_ptr<std::basic_streambuf<T> >
make_streambuf(
    file::stdio::Instance& file,
    std::ios_base::openmode mode = std::ios::in
)
{
    int fd = ::fileno(file.getFILE());
    auto filebuf = std::make_unique<__gnu_cxx::stdio_filebuf<T> >(fd, mode);

    return filebuf;
}

#endif

bool zdeflate(const fs::path& src, const fs::path& dest);
bool zinflate(const fs::path& src, const fs::path& dest);

} // namespace file::stdio
