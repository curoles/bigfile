#include "SmallFile.h"
#include "FileSystem.h"

#include <cassert>
#include <iostream>

int main()
{
    std::string fname = "test_small.txt";

    std::string written_str = "word1\n word2 word3\nword4\n";
#if 0
    {
        auto f = file::small::open(fname, "w");
        f.write(written_str);
        f.close();
        assert(!f.isOpen());
        assert(fs::exists(fname));
    }

    {
        auto f2 = file::small::open(fname, "r");
        assert(f2.isOpen());
        auto [received_str,read_err,read_errmsg] = f2.readAsString();
        if (read_err) {
            std::cout << "read error:" << read_errmsg << std::endl;
            return EXIT_FAILURE;
        }
        assert(0 == received_str.compare(written_str) && "shall read what was written");
        auto [received_str2,read_err2,read_errmsg2] = f2.readAsString(true,file::stdio::read_all_with_fgetc);
        assert(0 == received_str2.compare(written_str) && "shall read what was written");
    }

    {
        auto f = file::small::open(fname, "w"); // open for write only
        auto [received_str,read_err,read_errmsg] = f.readAsString();
        assert(read_err && "shall not be able to read file opened for writing only");
    }
#endif
    fs::remove(fname);

    return EXIT_SUCCESS;
}
