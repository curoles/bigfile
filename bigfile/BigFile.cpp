/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#include "BigFile.h"

#include <cassert>

#include "SmallFile.h"

using namespace file::big;

class Instance::Impl
{
    fs::path path_;
    size_t block_size_ = file::big::default_block_size;
    file::small::Instance lock_file_;
    file::small::Instance current_block_;
    size_t current_block_index_ = 0;
public:
   ~Impl();

    auto create_new(const fs::path& path, size_t block_size) -> file::error;

    auto block_size() { return block_size_; }

    auto try_to_lock() -> bool;
    auto unlock() -> void;

    auto is_open() -> bool {
        return lock_file_.is_open();
    }

    auto is_open_for_read_only() -> bool {
        return lock_file_.is_open_for_read_only();
    }

    auto write(const std::string& str) -> bool;

    auto read_string(bool from_beginning, size_t max_size) -> std::string;

};

Instance::Impl::~Impl()
{
    unlock();
}

auto Instance::Impl::create_new(
    const fs::path& path,
    size_t block_size
) -> file::error
{
    if (fs::exists(path)) {
        return file::error::ALREADY_EXISTS;
    }

    if (std::error_code ec; !fs::create_directory(path, ec)) {
        return file::error::CAN_NOT_CREATE; //CHECK_STD_ERR_CODE;
    }

    this->path_ = path;
    this->block_size_ = block_size;

    if (!try_to_lock()) {
        fs::remove_all(path);
        return file::error::CAN_NOT_GET_LOCK;
    }

    //create_meta_file(block_size);


    return file::error::NONE;
}

auto Instance::Impl::try_to_lock() -> bool
{
    // File System allows only one process to open file for writing.
    if (!lock_file_.open(path_ / ".lock", "w")) return false;

    lock_file_.set_at_beginning();
    if (lock_file_.is_range_locked() || !lock_file_.try_to_lock_range()) {
        lock_file_.close();
        return false;
    }

    lock_file_.write("1");

    return true;
}

auto Instance::Impl::unlock() -> void
{
    if (lock_file_.is_open()) {
        if (!lock_file_.is_open_for_read_only()) {
            lock_file_.set_at_beginning();
            lock_file_.write("0");
        }
        lock_file_.close();
    }
}

auto Instance::Impl::write(const std::string& str) -> bool
{
    if (!is_open() or is_open_for_read_only()) return false;

    if (!current_block_.is_open()) {
        current_block_.open(path_ / std::to_string(current_block_index_), "a");
        if (!current_block_.is_open()) return false;
    }

    size_t current_size = current_block_.file_size();
    if (current_size >= block_size_) {
        ++current_block_index_;
        current_block_.close();
        return this->write(str);
    }

    size_t available_space = block_size_ - current_size;
    if (available_space >= str.size())
    {
        return current_block_.write(str);
    }
    else
    {
        current_block_.write(str, available_space);
        current_block_.close();
        ++current_block_index_;
        return this->write(str.substr(available_space));
    }

    return true;
}

auto Instance::Impl::read_string(bool from_beginning, size_t max_size) -> std::string
{
    assert(!"not implemented");
    return "";
}

///////////////////////////////////////////////////////////////////////////////

Instance::~Instance() = default;
Instance& Instance::operator=(Instance&&) = default;

//Instance::Instance() : pImpl{std::make_unique<Impl>()} {}
Instance::Instance() : pImpl{new Impl(),[](Impl *impl) { delete impl; }} {}

file::error Instance::create_new(const fs::path& path, size_t block_size)
{
    return pImpl->create_new(path, block_size);
}

bool Instance::is_open()
{
    return pImpl->is_open();
}

bool Instance::open(const std::string& path, const std::string& mode)
{
    return false;//pImpl->open(path, mode); FIXME
}

void Instance::close()
{
    //pImpl->close(); FIXME
}

bool Instance::write(const std::string& str)
{
    return pImpl->write(str);
}

size_t Instance::block_size()
{
    return pImpl->block_size();
}

std::string Instance::read_string(bool from_beginning, size_t max_size)
{
    return pImpl->read_string(from_beginning, max_size);
}

