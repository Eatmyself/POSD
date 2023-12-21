#include "inmemory_drawing_mapper.h"
#include "inmemory_painter_mapper.h"

#include <sqlite3.h>
#include <string>
#include <map>
#include "drawing.h"
#include "triangle.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "domain_object.h"

InMemoryDrawingMapper * InMemoryDrawingMapper ::_instance = nullptr;

Drawing* InMemoryDrawingMapper ::find(std::string id) {
    auto it = _data.find(id);
    if (it != _data.end()){
        Painter * p = InMemoryPainterMapper::_instance()->find(it->second[0])
        Drawing * d = new Drawing(id, it->p);
        InMemoryDrawingMapper::instance()->load(d);
        return d;
    }
    return nullptr;
}

// add
void InMemoryDrawingMapper ::add(DomainObject * drawing) {
    Drawing * d = static_cast<Drawing *>(drawing);
    vector<std::string> tmp;
    tmp.push_back(d->painter()->id());
    tmp.push_back(d->getShapesAsString());
    _data[d->id()]=tmp;
}

// update
void InMemoryDrawingMapper ::update(std::string id) {
    DomainObject * drawing = getDomainObject(id);
    if(drawing){
        Drawing * d = static_cast<Drawing *>(drawing);
        vector<std::string> tmp;
        tmp.push_back(d->painter()->id());
        tmp.push_back(d->getShapesAsString());
        _data[d->id()]=tmp;
    }
    else
        throw std::string("object corresponding to ID is not in id map"); 
}

// delete
void InMemoryDrawingMapper ::del(std::string id) {
    auto it = _data.find(id);
    if (it != _data.end()){
        _data.erase(it);
    }
}

std::string InMemoryDrawingMapper ::updateStmt(DomainObject * domainObject) const {
    Drawing * drawing = static_cast<Drawing *>(domainObject);
    std::string stmt ("UPDATE drawing SET ");
    stmt += "painter = '" + drawing->painter()->id() + "', "
            "shapes = '" + drawing->getShapesAsString() + "' "
            " WHERE ID = '" + drawing->id() + "'";
    return stmt;
}

std::string InMemoryDrawingMapper ::findByIdStmt(std::string id) const {
    std::string stmt = "SELECT * FROM drawing WHERE ID = '" + id + "'";
    return stmt;
}

std::string InMemoryDrawingMapper ::addStmt(DomainObject * domainObject) const {
    Drawing * drawing = static_cast<Drawing *>(domainObject);
    std::string stmt = "INSERT INTO drawing values (";
    stmt += "'" + drawing->id() + "', ";
    stmt += "'" + drawing->painter()->id() + "', ";
    stmt += "'" + drawing->getShapesAsString() + "')";
    return stmt;
}

std::string InMemoryDrawingMapper ::deleteByIdStmt(std::string id) const {
    return "DELETE FROM drawing WHERE id = '" + id + "'";
}


InMemoryDrawingMapper * InMemoryDrawingMapper ::instance() {
    if(_instance == nullptr) {
        _instance = new InMemoryDrawingMapper ();
    }
    return _instance;
}

InMemoryDrawingMapper ::InMemoryDrawingMapper (): SQLiteAbstractMapper("resource/drawing.db") {
    _parser = new Parser(new Scanner(), new Builder());
}

int InMemoryDrawingMapper ::callback(void* notUsed, int argc, char** argv, char** colNames) {
    Painter * painter = PainterMapper::instance()->find(argv[1]);
    std::list<Shape *> shapes = InMemoryDrawingMapper ::instance()->convertShapes(argv[2]);
    Drawing * drawing = new Drawing(argv[0], painter, shapes);
    InMemoryDrawingMapper ::instance()->load(drawing);
    return 0;
}

std::list<Shape *> InMemoryDrawingMapper ::convertShapes(char * shape_string) {
    _parser->clear();
    _parser->setInput(shape_string);
    _parser->parse();
    return _parser->getShapes();
}

void InMemoryDrawingMapper ::cleanCache() {
    SQLiteAbstractMapper::cleanCache();
    _parser->clear();
}