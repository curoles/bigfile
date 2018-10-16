/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#pragma once

#include <memory>

#include "FileInterface.h"
#include "FileError.h"
#include "FileSystem.h"

namespace file::big {

constexpr size_t default_block_size = 128 * 1024 * 1024;

class Instance : public file::any::Interface
{
    class Impl;
    std::unique_ptr<Impl, void (*)(Impl *)> pImpl;
public:
    Instance();
   ~Instance();
    Instance(Instance&&) = default;
    Instance(const Instance&) = delete;

    Instance& operator=(Instance&&);
    Instance& operator=(const Instance&) = delete;

    auto create_new(
        const fs::path& path,
        size_t block_size = default_block_size) -> file::error;

    size_t block_size();

    bool is_open() override;
    bool open(const std::string& path, const std::string& mode) override;
    void close() override;
    bool write(const std::string& str) override;

};


}
