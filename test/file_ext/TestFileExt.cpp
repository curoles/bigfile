#include "FileExtension.h"
#include "FileSystem.h"

#include <cassert>
#include <iostream>
#include <algorithm>

int main()
{
    std::string lohi{"sOmE loW aNd SOME hiGH.TXT"};
    std::transform(lohi.begin(), lohi.end(), lohi.begin(), ::tolower);

    {auto [txt,err] = file::ext::isTextExt(".txt"); assert(txt && !err);}
    {auto [txt,err] = file::ext::isTextExt(".TXT"); assert(txt && !err);}
    {auto [txt,err] = file::ext::isTextExt(".html"); assert(txt && !err);}
    {auto [txt,err] = file::ext::isTextExt(".Html"); assert(txt && !err);}
    {auto [txt,err] = file::ext::isTextExt(".pdf"); assert(!txt && !err);}
    {auto [txt,err] = file::ext::isTextExt(".no such ext"); assert(err);}

    return EXIT_SUCCESS;
}
