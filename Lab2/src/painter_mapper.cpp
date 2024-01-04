#include "painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "sqlite_abstract_mapper.h"
#include "sqlite_painter_mapper.h"
#include "inmemory_painter_mapper.h"

PainterMapper* PainterMapper::instance() {
    if(DbMode::instance()->getMode()==mode::SQLite) {
        return SQLitePainterMapper::instance();
    }
    else return InMemoryPainterMapper::instance();
}

PainterMapper::PainterMapper(){}