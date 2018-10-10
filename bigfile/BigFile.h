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

namespace file::big {

class Instance : public file::any::Interface
{
    class Impl;
    std::unique_ptr<Impl> pImpl;
public:
    Instance();
   ~Instance();
    Instance(Instance&&) = default;
    Instance(const Instance&) = delete;

    Instance& operator=(Instance&&);
    Instance& operator=(const Instance&) = delete;

    bool isOpen() const override;
};

}
