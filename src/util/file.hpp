#pragma once

#include "string.hpp"
#include "result.hpp"
#include <fstream>

namespace lexer {

class FileLines {
    public:
        class Iter {
            public:
                Iter() = default;
                explicit Iter(std::ifstream*);
                Iter& operator++();
                bool operator==(Iter const&) const;
                bool operator!=(Iter const&) const;
                String const& operator*() const;

        private:
            bool at_end() const;
            
            std::ifstream* _file = nullptr;
            String _line;
        };

    public:
        explicit FileLines(FilePath const&);
        Iter begin();
        Iter end() const;
    
    private:
        std::ifstream _file;
};

inline
FileLines lines_in(FilePath const& path) {
    return FileLines(path);
}

Optional<String> read_file(FilePath const& path);

} //lexer
