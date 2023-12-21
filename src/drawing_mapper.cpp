#include "drawing_mapper.h"
#include "sqlite_painter_mapper.h"
#include "sqlite_drawing_mapper.h"

#include <sqlite3.h>
#include <string>
#include <map>
#include "drawing.h"
#include "triangle.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "domain_object.h"


DrawingMapper* DrawingMapper::instance() {
    if(DbMode::instance()->getMode()==mode::SQLite) {
        return SQLiteDrawingMapper::instance();
    }
    return SQLiteDrawingMapper::instance();
}

DrawingMapper::DrawingMapper(){}
