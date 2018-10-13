/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#pragma once

#include <string>

namespace file::any {

class Interface
{
public:
    virtual bool is_open() const = 0;
    virtual bool open(const std::string& path, const std::string& mode) = 0;
    virtual bool write(const std::string& str) = 0;

};

}
