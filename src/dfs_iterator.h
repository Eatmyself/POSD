#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H

#include "iterator.h"

class DfsIterator: public Iterator {
private:
    void Dfs(Node* step){
        List.push_back(step);
        if(step->ChildList().size()>0){
            for(int i=0;i<step->ChildList().size();i++){
                Dfs(step->ChildList()[i]);
            }
        }
        return;
    }
public:
    DfsIterator(Node* composite){
        this->now=1;
        Dfs(composite);
        if(isDone()) this->ptr=nullptr;
        else this->ptr=List[now];
    }

    void first(){
        now=1;
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

class BfsIterator: public Iterator {
private:
    void Bfs(Node* step){
        if(step->ChildList().size()>0){
            for(int i=0;i<step->ChildList().size();i++){
                List.push_back(step->ChildList()[i]);
            }
        }
        for(int i=0;i<step->ChildList().size();i++){
            Bfs(step->ChildList()[i]);
        }
        return;
    }
public:
    BfsIterator(Node* composite){
        this->now=0;
        Bfs(composite);
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

#endif // DFS_ITERATOR_H
