#if !defined(ITERATOR_H)
#define ITERATOR_H

#pragma once 

#include<list>

#include "node.h"

class Folder;
using namespace std;

class Iterator {
protected:
    int now;
    Node * ptr;
    vector<Node *> List;
public:
    ~Iterator(){
        List.clear();
        //cout<<"bye bye"<<endl;
    }
    virtual void first() = 0;
    virtual Node * currentItem() const = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
};

class FolderIterator : public Iterator {
public:
    FolderIterator(Folder* composite);
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;
};


#endif // ITERATOR_H
