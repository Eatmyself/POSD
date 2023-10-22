#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"

class FindByNameVisitor : public Visitor {
private:
    string targetName;
    std::list<string> pathList;
public:
    FindByNameVisitor(string name): targetName(name) {}

    void visitFile(File * file){
        if (file->name() == targetName) {
            pathList.push_back(file->path());
        }
    }

    void visitFolder(Folder * folder){
        if (folder->name() == targetName) {
            pathList.push_back(folder->path());
        }
        
        Iterator * it = folder->createIterator();
        it->first();
        while(!(it->isDone())){
            it->currentItem()->accept(this);
            it->next();
        }
    }

    std::list<string> getPaths() const{
        return pathList;
    }
};

