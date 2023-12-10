#include "unit_of_work.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "domain_object.h"
#include <list>
#include <iostream>


UnitOfWork * UnitOfWork::_instance = nullptr;

UnitOfWork::UnitOfWork() {}

UnitOfWork* UnitOfWork::instance() {
    if(_instance == nullptr) {
        _instance = new UnitOfWork();
    }
    return _instance;
}

void UnitOfWork::registerClean(DomainObject * domainObject) {
    _clean[domainObject->id()] = domainObject;
}

void UnitOfWork::registerDirty(DomainObject * domainObject) {
    _dirty[domainObject->id()] = domainObject;
    _clean.erase(domainObject->id());
}

void UnitOfWork::registerNew(DomainObject * domainObject) {
    _new[domainObject->id()] = domainObject;
}

void UnitOfWork::registerDeleted(DomainObject * domainObject) {
    if(_clean.count(domainObject->id()))_clean.erase(domainObject->id());
    else if(_new.count(domainObject->id()))_new.erase(domainObject->id());
    else if(_dirty.count(domainObject->id()))_dirty.erase(domainObject->id());
    _deleted[domainObject->id()] = domainObject;
}

bool UnitOfWork::inClean(std::string id) const {
    return _clean.count(id);
}

bool UnitOfWork::inDirty(std::string id) const {
    return _dirty.count(id);
}

bool UnitOfWork::inNew(std::string id) const {
    return _new.count(id);
}

bool UnitOfWork::inDeleted(std::string id) const {
    return _deleted.count(id);
}

void UnitOfWork::commit() {
    for(auto dirty : _dirty) {
        if(Drawing *dr = dynamic_cast<Drawing*>(dirty.second)) {
            DrawingMapper::instance()->update(dirty.second->id());
        }
        else if(Painter *pa = static_cast<Painter*>(dirty.second)) {
            PainterMapper::instance()->update(dirty.second->id());   
        }
        else throw "exception";
        registerClean(dirty.second);
    }
    _dirty.clear();
    for(auto newObj : _new) {
        if(Drawing *dr = dynamic_cast<Drawing*>(newObj.second)) {
            DrawingMapper::instance()->add(newObj.second);
        }
        else if(Painter *pa = static_cast<Painter*>(newObj.second)) {
            PainterMapper::instance()->add(newObj.second);  
        }
        else throw "exception";
        registerClean(newObj.second);
    }
    _new.clear();
    for(auto delObj : _deleted) {
        if(Drawing *dr = dynamic_cast<Drawing*>(delObj.second)) {
            DrawingMapper::instance()->del(delObj.second->id());
        }
        else if(Painter *pa = static_cast<Painter*>(delObj.second)) {
            PainterMapper::instance()->del(delObj.second->id()); 
        }
        else throw "exception";
    }
    _deleted.clear();
}