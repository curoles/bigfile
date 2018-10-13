#include "SmallFile.h"
#include "FileSystem.h"

#include <cassert>
#include <iostream>

int main()
{
    std::string fname = "test_small.txt";

    std::string written_str = "word1\n word2 word3\nword4\n";

    {
        auto f = file::small::open(fname, "w");
        f.write(written_str);
        f.close();
        assert(!f.is_open());
        assert(fs::exists(fname));
    }

    {
        auto f2 = file::small::open(fname, "r");
        assert(f2.is_open());
        auto [received_str,read_err,read_errmsg] = f2.read_as_string();
        if (read_err) {
            std::cout << "read error:" << read_errmsg << std::endl;
            return EXIT_FAILURE;
        }
        assert(0 == received_str.compare(written_str) && "shall read what was written");
        auto [received_str2,read_err2,read_errmsg2] = f2.read_as_string();
        assert(0 == received_str2.compare(written_str) && "shall read what was written");
    }

    {
        auto f = file::small::open(fname+"dummy", "w"); // open for write only
        auto [received_str,read_err,read_errmsg] = f.read_as_string();
        assert(read_err && "shall not be able to read file opened for writing only");
    }

    {
        auto f = file::small::open(fname, "r");
        std::cout << std::get<0>(f.read_as_string()) << std::endl;
        auto [lines,err] = f.read_all_lines();
        for (auto& line : lines) {
            std::cout << line << std::endl;
        }
    }

    fs::remove(fname);

    return EXIT_SUCCESS;
}
