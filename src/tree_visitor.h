#pragma once

#include "visitor.h"
#include "order_by.h"

class TreeVisitor: public Visitor {
private:
    string _result;
    OrderBy ob;
    int n = 0;
public:
    TreeVisitor(OrderBy orderBy): ob(orderBy){
        _result += ".\n";
    }

    void visitFile(File * file){
        return;
    }

    void visitFolder(Folder * folder){
        Iterator * it = folder->createIterator(ob);
        it->first();
        while(!(it->isDone())){
            Node * tmp = it->currentItem();
            it->next();
            if(it->isDone()){
                for(int i=0;i<n;i++) _result += "│   ";
                _result += "└── " + tmp->name() + "\n";
            }
            else{
                for(int i=0;i<n;i++) _result += "│   ";
                _result += "├── " + tmp->name() + "\n";
            }
            n++;
            tmp->accept(this);
            n--;
        }
    }

    string getTree() const{
        return _result;
    }
};