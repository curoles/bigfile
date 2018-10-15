/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#include "BigFile.h"

#include "SmallFile.h"

using namespace file::big;

class Instance::Impl
{
    fs::path path_;
    size_t block_size_ = file::big::default_block_size;
    file::small::Instance lock_file_;
    //file::small::Instance current_block_;
public:
   ~Impl();

    auto create_new(const fs::path& path, size_t block_size) -> file::error;

    auto try_to_lock() -> bool;
    auto unlock() -> void;

    auto is_open() -> bool {
        return lock_file_.is_open();
    }
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

    if (!try_to_lock()) {
        return file::error::CAN_NOT_GET_LOCK;
    }

    //create_meta_file(block_size);


    return file::error::NONE;
}

auto Instance::Impl::try_to_lock() -> bool
{
    // File System allows only one process to open file for writing.
    if (!lock_file_.open(path_ /= ".lock", "w")) return false;

    lock_file_.set_at_beginning();
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
    return false;//pImpl->open(path, mode);
}

void Instance::close()
{
    //pImpl->close();
}

bool Instance::write(const std::string& str)
{
    return false;//pImpl->write(str);
}

