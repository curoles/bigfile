/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#pragma once

namespace file {

struct Info
{
    bool isText; // text or binary
    bool isBig;
    bool isJournal; // append+read
    //text encoding
    //zipped
    //encrypted
};

}
