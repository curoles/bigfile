/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#include "SmallFile.h"

#include "StdioFile.h"

using namespace file::small;

class Instance::Impl
{
    file::stdio::Instance file_;
public:
    Impl(){
        static_assert(sizeof(Impl) > 0, "class Impl must be complete");
    }
   ~Impl(){}

    bool is_open() const {
        return file_.is_open();
    }
    bool open(const std::string& path, const std::string& mode) {
        return file_.open(path, mode);
    }
    bool write(const std::string& str) {
        return file_.write(str);
    }

};


Instance::~Instance() = default;
Instance& Instance::operator=(Instance&&) = default;

//Instance::Instance() : pImpl{std::make_unique<Impl>()} {}
Instance::Instance() : pImpl{new Impl(),[](Impl *impl) { delete impl; }} {}

bool Instance::is_open() const
{
    return pImpl->is_open();
}

bool Instance::open(const std::string& path, const std::string& mode)
{
    return pImpl->open(path, mode);
}

bool Instance::write(const std::string& str)
{
    return pImpl->write(str);
}


