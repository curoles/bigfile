/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#pragma once

#include <memory>
#include <vector>
//#include <experimental/propagate_const>

#include "FileInterface.h"
#include "FileError.h"

namespace file::small {

class Instance : public file::any::Interface
{
    class Impl;
    std::unique_ptr<Impl, void (*)(Impl *)> pImpl;
    //std::experimental::propagate_const<std::unique_ptr<Impl>> pImpl;
public:
    Instance();
   ~Instance();
    Instance(Instance&&) = default;
    Instance(const Instance&) = delete;

    Instance& operator=(Instance&&);
    Instance& operator=(const Instance&) = delete;

    bool is_open() override;
    bool open(const std::string& path, const std::string& mode) override;
    void close() override;
    bool write(const std::string& str) override;
    bool write(const std::string& str, size_t len);

    auto read_as_string() -> std::tuple<std::string,file::error,int>;
    auto read_all_lines() -> std::tuple<std::vector<std::string>,bool>;

    auto set_at_beginning() -> void;
    auto is_open_for_read_only() -> bool;

    bool is_range_locked(int len = 0 /*0 means infinity*/);
    bool try_to_lock_range(int len = 0);
    bool unlock_range(int len = 0);

    size_t file_size();
};

static inline
auto open(const std::string& fname, const std::string& mode) -> file::small::Instance
{
    file::small::Instance file;
    file.open(fname, mode);

    return file;
}

}
