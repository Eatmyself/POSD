#pragma once

#include <string>
#include <iostream>
#include <sqlite3.h>
#include <map>

#include "painter.h"
#include "sqlite_abstract_mapper.h"
#include "painter_mapper.h"


class InMemoryPainterMapper: public SQLiteAbstractMapper, public PainterMapper{
public:
    
    void add(DomainObject * Painter);

    Painter* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    static InMemoryPainterMapper* instance();

    void cleanCache();

protected:
    InMemoryPainterMapper();

    static int callback(void* notUsed, int argc, char** argv, char** colNames);

    std::string addStmt(DomainObject * domainObject) const;
    std::string findByIdStmt(std::string id) const;
    std::string updateStmt(DomainObject * domainObject) const;
    std::string deleteByIdStmt(std::string id) const;
    
private:
    static InMemoryPainterMapper* _instance;
    std::map<std::string, std::string> _data;
};