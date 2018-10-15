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

    bool is_open() const override;
    bool open(const std::string& path, const std::string& mode) override;
    void close() override;
    bool write(const std::string& str) override;

    auto read_as_string() -> std::tuple<std::string,file::error,int>;
    auto read_all_lines() -> std::tuple<std::vector<std::string>,bool>;

};

static inline
auto open(const std::string& fname, const std::string& mode) -> file::small::Instance
{
    file::small::Instance file;
    file.open(fname, mode);

    return file;
}

}
