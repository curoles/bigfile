/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#include "FileExtension.h"

#include <unordered_map>
#include <algorithm>

static const
std::unordered_map<std::string, bool> text_type_by_ext_map = {
    {".txt",  true},
    {".html", true},
    {".pdf",  false},
    {".zip",  false},
};

auto file::ext::isTextExt(const std::string& extname) -> std::tuple<bool,bool/*err*/>
{
    std::string ext{extname};
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    auto search = text_type_by_ext_map.find(ext);
    bool isFoundInMap = search != text_type_by_ext_map.end();
    bool isText = isFoundInMap ? search->second : /*default*/false;

    return std::make_tuple(isText, /*err=*/!isFoundInMap);
}

