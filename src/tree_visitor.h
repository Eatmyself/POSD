#pragma once

#include "visitor.h"
#include "order_by.h"

class TreeVisitor: public Visitor {
private:
    string _result;
    OrderBy ob;
    int n = 0;
    bool last = false;
public:
    TreeVisitor(OrderBy orderBy): ob(orderBy){
        _result += ".\n";
    }

    void visitFile(File * file){
        for(int i=0;i<n;i++) _result += "│   ";
        if(last) _result += "└── " + file->name() + "\n";
        else _result += "├── " + file->name() + "\n";
        last = false;
    }

    void visitFolder(Folder * folder){
        for(int i=0;i<n;i++) _result += "│   ";
        if(last) _result += "└── " + folder->name() + "\n";
        else _result += "├── " + folder->name() + "\n";
        last = false;
        Iterator * it = folder->createIterator(ob);
        n++;
        it->first();
        while(!(it->isDone())){
            Node * tmp = it->currentItem();
            it->next();
            if(it->isDone()){
                last = true;
            }
            tmp->accept(this);
        }
        n--;
    }

    string getTree() const{
        return _result;
    }
};