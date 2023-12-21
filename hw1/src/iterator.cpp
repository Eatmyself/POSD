#include<list>

#include "iterator.h"
#include "folder.h"

FolderIterator::FolderIterator(Folder* composite){
    this->List = composite->ChildList();
    this->now=0;
    if(isDone()) this->ptr=nullptr;
    else this->ptr=List[now];
}
void FolderIterator::first(){
    now=0;
    if(isDone()) ptr=nullptr;
    else ptr=List[now];
}
Node * FolderIterator::currentItem() const{
    return ptr;
}
void FolderIterator::next(){
    now++;
    if(isDone()) ptr=nullptr;
    else ptr=List[now];
    if(now>List.size()) now=List.size();
}
bool FolderIterator::isDone() const{
    if(now>=List.size())return true;
    else return false;
}


