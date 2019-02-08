#include "db.hpp"
#include <gsl/gsl>

//TODO sqlite3 prepared statements

namespace lexer {

DBRow::Iter::Iter(DBRowData const& row, int col)
    : _row(row)
    , _col(col)
    {
}

DBRow::Iter& DBRow::Iter::operator++() {
    if (_col < _row.size) {
        ++_col;
    }

    return *this;
}

bool DBRow::Iter::operator==(Iter const& other) const {
    return (at_end() && other.at_end())
        || (_row.values == other._row.values && _col == other._col);
}

bool DBRow::Iter::operator!=(Iter const& other) const {
    return !this->operator==(other);
}

DBRow::Iter::Pair DBRow::Iter::operator*() {
    return { _row.names[_col], _row.values[_col] };
}

bool DBRow::Iter::at_end() const {
    return _col < 0 
        || _col >= _row.size;
}

DBRow::DBRow(DBRowData const& row)
    : _row(row)
    {
}

DBRow::Iter DBRow::begin() const {
    return Iter(_row, 0);
}

DBRow::Iter DBRow::end() const {
    return Iter(_row, _row.size);
}

static
int null_callback(void*, int, char**, char**) {
    return SQLITE_OK;
}

DB::DB(FilePath const& filename) {
    open(filename);
}

void DB::open(FilePath const& filename) {
    _db.release();
    int const open_flags = SQLITE_OPEN_READWRITE
                         | SQLITE_OPEN_CREATE
                         | SQLITE_OPEN_FULLMUTEX;

    sqlite3* db = nullptr;
    int const e = sqlite3_open_v2(filename.c_str(), &db, open_flags, nullptr);
    _db.reset(db);
    
    if (e != SQLITE_OK) {
        // TODO differentiate db-open error from query error.
        throw SQLException(sqlite3_errmsg(db));
    }
}

int DB::query(SQL const& query, SQLCallback* callback, void* callback_data) {
    char* query_errmsg = nullptr;
    auto _ = gsl::finally([&]() { 
        sqlite3_free(query_errmsg); 
        });
    
    int const e = sqlite3_exec(_db.get(), query.c_str(), callback, 
            callback_data, &query_errmsg);

    switch (e) {
        case SQLITE_OK:
        case SQLITE_ABORT:
            break;
        default:
            throw SQLException(
                sqlite3_errmsg(_db.get())
                );
    }

    return e;
}

int DB::query(SQL const& query) {
    return this->query(query, null_callback, nullptr);
}

} //lexer
