/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#pragma once

#include <cstdio>

namespace file::zlib {

bool zdeflate(FILE* src, FILE* dest);
bool zinflate(FILE* src, FILE* dest);

}
