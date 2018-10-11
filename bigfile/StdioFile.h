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
#include <cstdio>
#include <cerrno>
#include <cstring>

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

    void setAtBeginning() {
        ::fseek(file_, 0, SEEK_SET);
    }

    std::tuple<std::string,bool,std::string>
    readAsString(bool fromBeginning=true, void (*reader)(FILE*,std::string&) = read_all_with_fread)
    {
        std::string s, errmsg; bool err = false;

        if (fromBeginning) setAtBeginning();
        reader(file_,s);

        if (::ferror(file_)) {
            err = true; errmsg = ::strerror(::ferror(file_));
        } else if (! ::feof(file_)) {
            err = true; errmsg = "End of file NOT reached";
        }

        return std::make_tuple(s, err, errmsg);
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
