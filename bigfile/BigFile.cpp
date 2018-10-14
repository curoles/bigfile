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
    file::small::Instance file_;
public:
    bool is_open() const {
        return false;//file_.is_open();
    }
};


Instance::~Instance() = default;
Instance& Instance::operator=(Instance&&) = default;

//Instance::Instance() : pImpl{std::make_unique<Impl>()} {}
Instance::Instance() : pImpl{new Impl(),[](Impl *impl) { delete impl; }} {}


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

