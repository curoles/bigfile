/**
 * @file
 * @brief
 * @author    Igor Lesik 2018
 * @copyright Igor Lesik 2018
 *
 */
#include "SmallFile.h"

#include "StdioFile.h"

using namespace file::small;

class Instance::Impl
{
    file::stdio::Instance file_;
public:
    Impl(){
        static_assert(sizeof(Impl) > 0, "class Impl must be complete");
    }
   ~Impl(){}

    bool is_open() const {
        return file_.is_open();
    }
    bool open(const std::string& path, const std::string& mode) {
        return file_.open(path, mode);
    }
    void close() {
        file_.close();
    }
    bool write(const std::string& str) {
        return file_.write(str);
    }
    auto read_as_string() -> std::tuple<std::string,bool,std::string> {
        return file_.read_as_string();
    }
    auto read_all_lines() -> std::tuple<std::vector<std::string>,bool> {
        std::vector<std::string> all_lines;
        file_.set_at_beginning();

        auto streambuf = file::stdio::make_streambuf<char>(file_);
        std::istream instream(streambuf.get());

        for (std::string line; std::getline(instream, line); ) {
            all_lines.push_back(line);
        }

        return std::make_tuple(all_lines,/*err*/false);
    }

};


Instance::~Instance() = default;
Instance& Instance::operator=(Instance&&) = default;

//Instance::Instance() : pImpl{std::make_unique<Impl>()} {}
Instance::Instance() : pImpl{new Impl(),[](Impl *impl) { delete impl; }} {}

bool Instance::is_open() const
{
    return pImpl->is_open();
}

bool Instance::open(const std::string& path, const std::string& mode)
{
    return pImpl->open(path, mode);
}

void Instance::close()
{
    return pImpl->close();
}

bool Instance::write(const std::string& str)
{
    return pImpl->write(str);
}

auto Instance::read_as_string() -> std::tuple<std::string,bool,std::string>
{
    return pImpl->read_as_string();
}

auto Instance::read_all_lines() -> std::tuple<std::vector<std::string>,bool>
{
    return pImpl->read_all_lines();
}

