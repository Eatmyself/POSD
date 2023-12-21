#include "painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "abstract_mapper.h"

PainterMapper* PainterMapper::_instance = nullptr;
PainterMapper::PainterMapper() {}

PainterMapper* PainterMapper::instance(){
    if (_instance == nullptr){
        _instance = new PainterMapper();
    }
    return _instance;
}

Painter* PainterMapper::find(std::string id){
    return static_cast<Painter*>(abstractFind(id, PainterMapper::callback));
}

std::string PainterMapper::findByIdStmt(std::string id) const{
    std::string stmt = "SELECT * FROM painter WHERE ID='" + id + "'";
    return stmt;
}
    
void PainterMapper::add(DomainObject * Painter){
    abstractAdd(Painter);
}

std::string PainterMapper::addStmt(DomainObject * domainObject) const{
    Painter* painter = static_cast<Painter*>(domainObject);
    std::string stmt = "INSERT INTO painter(ID, name) values ('" + painter->id() + "', '" + painter->name() + "')";
    return stmt;
}

void PainterMapper::update(std::string id) {
    DomainObject* domainObject = PainterMapper::instance()->find(id);
    abstractUpdate(domainObject);
}

std::string PainterMapper::updateStmt(DomainObject * domainObject) const{
    Painter* painter = static_cast<Painter*>(domainObject);
    std::string stmt = "UPDATE painter SET name='" + painter->name() + "' WHERE ID='" + painter->id() + "'";
    return stmt;
}

void PainterMapper::del(std::string id){
    abstractDelete(id);
}

std::string PainterMapper::deleteByIdStmt(std::string id) const{
    std::string stmt = "DELETE FROM painter WHERE ID='" + id + "'";
    return stmt;
}

int PainterMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    Painter* painter = new Painter(argv[0], argv[1]);
    PainterMapper::instance()->load(painter);
    return 0;
}

