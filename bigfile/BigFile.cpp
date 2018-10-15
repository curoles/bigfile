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
    size_t block_size_ = file::big::default_block_size;
    file::small::Instance current_file_;
public:
    auto create_new(const fs::path& path, size_t block_size) -> file::error;

    auto is_open() const -> bool {
        return current_file_.is_open();
    }
};

auto Instance::Impl::create_new(
    const fs::path& path,
    size_t block_size
) -> file::error
{
    if (fs::exists(path)) {
        return file::error::ALREADY_EXISTS;
    }

    std::error_code ec;
    if (!create_directory(path, ec)) {
        return file::error::CHECK_STD_ERR_CODE;
    }

    //lock directory for exclusive writing

    //create_meta_file(block_size);


    return file::error::NONE;
}

Instance::~Instance() = default;
Instance& Instance::operator=(Instance&&) = default;

//Instance::Instance() : pImpl{std::make_unique<Impl>()} {}
Instance::Instance() : pImpl{new Impl(),[](Impl *impl) { delete impl; }} {}

file::error Instance::create_new(const fs::path& path, size_t block_size)
{
    return pImpl->create_new(path, block_size);
}

bool Instance::is_open() const
{
    return false;//pImpl->is_open();
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

