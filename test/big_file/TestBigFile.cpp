#include "BigFile.h"
#include "FileSystem.h"

#include <cassert>
#include <iostream>

int main()
{
    fs::path fname = "test_big.txt";
    fs::remove_all(fname);

    std::string written_str = "123456789\n123456789\n123456789\n";

    {
        file::big::Instance f;
        file::error err = f.create_new(fname, 10);
        if (!!err) {
            std::cout << "Error: " << file::errmsg(err) << std::endl;
            return 1;
        }
        assert(f.is_open());
        f.write(written_str);
        assert( fs::exists(fname / "0") );
        assert( fs::exists(fname / "1") );
        assert( fs::exists(fname / "2") );
    }

#if 0

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
#endif

    //TODO fs::remove_all(fname);

    return EXIT_SUCCESS;
}
