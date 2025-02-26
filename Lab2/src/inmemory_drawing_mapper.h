#pragma once

#include <string>
#include <vector>
#include <map>

#include <sqlite3.h>

#include "drawing.h"
#include "sqlite_abstract_mapper.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "scanner.h"
#include "builder.h"
#include "parser.h"

class InMemoryDrawingMapper : public SQLiteAbstractMapper, public DrawingMapper {
public:

    ~InMemoryDrawingMapper () {
        delete _parser;
    }

    void add(DomainObject * Drawing);

    Drawing* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    static InMemoryDrawingMapper * instance();

    void cleanCache();

protected:
    InMemoryDrawingMapper ();

    static int callback(void* notUsed, int argc, char** argv, char** colNames);

    std::list<Shape *> convertShapes(char * shape_string);

    std::string addStmt(DomainObject * domainObject) const;
    std::string findByIdStmt(std::string id) const;
    std::string updateStmt(DomainObject * domainObject) const;
    std::string deleteByIdStmt(std::string id) const;

private:
    static InMemoryDrawingMapper * _instance;
    Parser * _parser;
    std::map<std::string, std::vector<std::string>> _data;
};