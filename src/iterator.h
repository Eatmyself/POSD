#if !defined(ITERATOR_H)
#define ITERATOR_H

#pragma once 

#include<list>

#include "node.h"

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
    FolderIterator(Node* composite){
        this->List = composite->ChildList();
        this->now=0;
        if(isDone()) this->ptr=nullptr;
        else this->ptr=List[now];
    }
    void first(){
        now=0;
        if(isDone()) ptr=nullptr;
        else ptr=List[now];
    }
    Node * currentItem() const{
        return ptr;
    }
    void next(){
        now++;
        if(isDone()) ptr=nullptr;
        else ptr=List[now];
        if(now>List.size()) now=List.size();
    }
    bool isDone() const{
        if(now>=List.size())return true;
        else return false;
    }
};


#endif // ITERATOR_H
