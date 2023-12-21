#pragma once

#include "visitor.h"
#include "order_by.h"
#include <list>

using namespace std;

class TreeVisitor: public Visitor {
private:
    string _result;
    OrderBy ob;
    list<string> tab;
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
            for (auto it = tab.begin(); it != tab.end(); ++it) _result += (*it);
            if(it->isDone()){
                _result += "└── " + tmp->name() + "\n";
                tab.push_back ("    ");
            }
            else{
                _result += "├── " + tmp->name() + "\n";
                tab.push_back ("│   ");
            }
            tmp->accept(this);
            tab.pop_back();
        }
    }

    string getTree() const{
        return _result;
    }
};