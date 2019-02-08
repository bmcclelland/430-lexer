#include "file.hpp"

namespace lexer {

FileLines::FileLines(FilePath const& path)
    : _file(path)
    {    
}

FileLines::Iter FileLines::begin() {
    return Iter(&_file);
}

FileLines::Iter FileLines::end() const {
    return Iter();
}

FileLines::Iter::Iter(std::ifstream* file)
    : _file(file)
    {
}

FileLines::Iter& FileLines::Iter::operator++() {
    if (!at_end()) {
        getline(*_file, _line);
    }

    return *this;
}

bool FileLines::Iter::operator==(Iter const& o) const {
    return (at_end() == o.at_end())
        || (_file && o._file && _file->tellg() == o._file->tellg());
}

bool FileLines::Iter::operator!=(Iter const& o) const {
    return !(*this == o);
}

String const& FileLines::Iter::operator*() const {
    return _line;
}

bool FileLines::Iter::at_end() const {
    return !_file
        || !(*_file);
}

Optional<String> read_file(FilePath const& path) {
    std::ifstream file(path);

    if (!file) {
        return failure;
    }

    String s;
    file.seekg(0, std::ios::end);
    s.reserve(static_cast<size_t>(file.tellg()));
    file.seekg(0, std::ios::beg);

    s.assign((std::istreambuf_iterator<char>(file)),
              std::istreambuf_iterator<char>());

    return s;
}

} //lexer
