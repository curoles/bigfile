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
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <iostream>

namespace file::stdio {

static inline
void read_all_with_fgetc(FILE* fp, std::string& s)
{
    int c; while ((c = ::fgetc(fp)) != EOF) { s += (char)c; }
}

static inline
void read_all_with_fread(FILE* fp, std::string& s)
{
    char buf[1024]; size_t num_bytes_received;
    while ((num_bytes_received = ::fread(buf, 1, sizeof(buf), fp)) != 0) {
        s.append(buf, num_bytes_received);
    }
}

class Instance
{
    FILE* file_ = nullptr;
public:
    Instance():file_{nullptr}{}
   ~Instance() {
        close();
    }
    Instance(Instance&&) = default;
    Instance(const Instance&) = delete;

    Instance& operator=(Instance&&) = delete;
    Instance& operator=(const Instance&) = delete;

    bool is_open() const {
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

    bool write(const std::string& str) {
        int ret = ::fputs(str.c_str(), file_);
        return ret > 0;
    }

    void set_at_beginning() {
        ::fseek(file_, 0, SEEK_SET);
    }

    std::tuple<std::string,bool,std::string>
    read_as_string(bool from_beginning = true,
                   void (*reader)(FILE*,std::string&) = read_all_with_fread)
    {
        std::string s, errmsg; bool err = false;

        if (from_beginning) set_at_beginning();
        reader(file_,s);

        if (::ferror(file_)) {
            err = true; errmsg = ::strerror(::ferror(file_));
        } else if (! ::feof(file_)) {
            err = true; errmsg = "End of file NOT reached";
        }

        return std::make_tuple(s, err, errmsg);
    }

    auto for_each_char(std::function<bool(char)> f) -> void
    {
        int c; while ((c = ::fgetc(file_)) != EOF && f((char)c)) { /*keep running*/ }
    }
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

} // namespace file::stdio
