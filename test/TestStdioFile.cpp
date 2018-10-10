#include "StdioFile.h"
//#include "SmallFile.h"

int main()
{
    auto f = file::stdio::open("test_stdio.txt", "w");
    f.write("word1 word2\n word3");

    //auto sf = file::small::open("test_small.txt", "w");
    //sf.write("w1\nword2\nword3");

    return 0;
}
