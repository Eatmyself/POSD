#include <string>
#include <iostream>
#include <sqlite3.h>

#include "inmemory_painter_mapper.h"
#include "sqlite_abstract_mapper.h"

InMemoryPainterMapper* InMemoryPainterMapper::_instance = nullptr;

Painter* InMemoryPainterMapper::find(std::string id) {
    auto it = _data.find(id);
    if (it != _data.end()){
        Painter* p = new Painter(id, it->second);
        InMemoryPainterMapper::instance()->load(p);
        return p;
    }
    return nullptr;
}

// add
void InMemoryPainterMapper::add(DomainObject * painter) {
    Painter * p = static_cast<Painter *>(painter);
    _data[p->id()]=p->name();
}

// update
void InMemoryPainterMapper::update(std::string id) {
    DomainObject * painter = getDomainObject(id);
    if(painter){
        Painter * p = static_cast<Painter *>(painter);
         _data[p->id()]=p->name();
    }
    else
        throw std::string("object corresponding to ID is not in id map"); 
}

// delete
void InMemoryPainterMapper::del(std::string id) {
    auto it = _data.find(id);
    if (it != _data.end()){
        _data.erase(it);
    }
}

std::string InMemoryPainterMapper::updateStmt(DomainObject * domainObject) const {
    Painter * painter = static_cast<Painter *>(domainObject);
    std::string stmt ("UPDATE painter SET ");
    stmt += "name = '" + painter->name() + "' "
            " where ID = '" + painter->id() + "'";
    return stmt;
}

std::string InMemoryPainterMapper::findByIdStmt(std::string id) const {
    return "SELECT * FROM painter WHERE ID = '" + id + "'";
}

std::string InMemoryPainterMapper::addStmt(DomainObject * domainObject) const {
    Painter * painter = static_cast<Painter *>(domainObject);
    std::string stmt = "INSERT INTO painter values (";
    stmt += "'" + painter->id() + "', ";
    stmt += "'" + painter->name() + "')";
    return stmt;
}

std::string InMemoryPainterMapper::deleteByIdStmt(std::string id) const {
    return "DELETE FROM painter WHERE id = '" + id + "'";
}


InMemoryPainterMapper* InMemoryPainterMapper::instance() {
    if(_instance == nullptr) {
        _instance = new InMemoryPainterMapper();
    }
    return _instance;
}

InMemoryPainterMapper::InMemoryPainterMapper(): SQLiteAbstractMapper("resource/painter.db") {
}

int InMemoryPainterMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    Painter* painter = new Painter(argv[0], argv[1]);
    InMemoryPainterMapper::instance()->load(painter);
    return 0;
}

void InMemoryPainterMapper::cleanCache() {
    SQLiteAbstractMapper::cleanCache();
}