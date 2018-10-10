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
    bool isOpen() const {
        return file_.isOpen();
    }
};


Instance::~Instance() = default;
Instance& Instance::operator=(Instance&&) = default;

Instance::Instance() : pImpl{std::make_unique<Impl>()} {}

bool Instance::isOpen() const
{
    return pImpl->isOpen();
}

