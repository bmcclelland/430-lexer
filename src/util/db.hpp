#pragma once

#include "sqlite.hpp"
#include "string.hpp"
#include "memory.hpp"
#include "exception.hpp"

namespace lexer {

using SQL = String;

using SQLCallback = int(void*,int,char**,char**);

using SQLException = RuntimeError<struct SQLException_>;

struct DBRowData {
    int    size;
    char** values;
    char** names;
};

class DBRow {
    public:
        class Iter {
            public:
                Iter(DBRowData const&, int col);
                Iter& operator++();
                bool operator==(Iter const&) const;
                bool operator!=(Iter const&) const;
            
                struct Pair {
                    char const* name;
                    char const* value;
                };

                Pair operator*();

        private:
            DBRowData _row;
            int       _col;
        
            bool at_end() const;
    };

    public:
        explicit DBRow(DBRowData const&);
        Iter begin() const;
        Iter end() const;
    
    private:
        DBRowData _row;
};

class DB {
    public:
        explicit DB(FilePath const&);

        template <typename F>
        int query(SQL const& sql, F const& func) {
            // func is passed in as the callback data, then called
            //  on the row data. This allows closures to work.
            auto callback = 
                [](void* data, int size, char** values, char** names) 
                {
                F const* f = static_cast<F const*>(data);
                return (*f)(DBRow(
                    { size, values, names }
                    ));
            };

            // const_cast here is because sqlite3 requires a void*.
            // I swear on my life not to mutate func.
            return query(sql, callback, &const_cast<F&>(func));
        }

        int query(SQL const&);

    private:
        void open(FilePath const&);
        int query(SQL const&, SQLCallback*, void* callback_data);
        
        struct Deleter {
            void operator()(sqlite3* p) const {
                sqlite3_close(p);
            }
        };

        UniquePtr<sqlite3, Deleter> _db;
};

} //lexer
