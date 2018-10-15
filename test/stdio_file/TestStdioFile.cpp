#include "StdioFile.h"
#include "FileSystem.h"

#include <cassert>
#include <iostream>

int main()
{
    std::string fname = "test_stdio.txt";

    std::string written_str = "word1\n word2 word3\nword4\n";

    {
        auto f = file::stdio::open(fname, "w");
        f.write(written_str);
        f.close();
        assert(!f.is_open());
        assert(fs::exists(fname));
    }

    {
        auto f2 = file::stdio::open(fname, "r");
        assert(f2.is_open());
        auto [received_str,read_err,ferr] = f2.read_as_string();
        if (file::is_err(read_err)) {
            std::cout << "read error: " << file::errmsg(read_err,ferr) << std::endl;
            return EXIT_FAILURE;
        }
        assert(0 == received_str.compare(written_str) && "shall read what was written");
        auto [received_str2,read_err2,read_errmsg2] = f2.read_as_string(true,file::stdio::read_all_with_fgetc);
        assert(0 == received_str2.compare(written_str) && "shall read what was written");
    }

    {
        auto f = file::stdio::open(fname+".dummy", "w"); // open for write only
        auto [received_str,read_err,read_errmsg] = f.read_as_string();
        assert(!!read_err && "shall not be able to read file opened for writing only");
        fs::remove(fname+".dummy");
    }

    {
        auto f = file::stdio::open(fname, "r");
        size_t numLines = file::stdio::count_lines(f);
        assert(numLines == 3);
    }

    {
        auto f = file::stdio::open(fname, "r");
        auto streambuf = file::stdio::make_streambuf<char>(f);
        std::istream instream(streambuf.get());
        assert(instream.good());
        for (std::string line; std::getline(instream, line); ) {
            std::cout << line << std::endl;
        }
        assert(instream.eof());
    }

    {
        std::string fname_zip = fname+".zip";
        std::string fname_unzip = fname_zip+".txt";
        assert(file::stdio::zdeflate(fname, fname_zip));
        assert(file::stdio::zinflate(fname_zip, fname_unzip));

        auto f = file::stdio::open(fname_unzip, "r");
        auto [received_str,read_err,read_errmsg] = f.read_as_string();
        if (!!read_err) {
            std::cout << "read error:" << read_errmsg << std::endl;
            return EXIT_FAILURE;
        }
        assert(0 == received_str.compare(written_str) && "shall read what was written");
        fs::remove(fname_zip);
        fs::remove(fname_unzip);
    }

    fs::remove(fname);

    return EXIT_SUCCESS;
}
