#if !defined(FOLDER)
#define FOLDER

#include <iostream>
#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"

#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

class Folder: public Node {
private:
    Iterator * tmp;
    void BfsDelete(Node* step, string path){
        if(step->ChildList().size()>0){
            for(int i=0;i<step->ChildList().size();i++){
                if(step->ChildList()[i]->path()==path){
                    step->removeChild(path);
                    return;
                }
            }
            for(int i=0;i<step->ChildList().size();i++){
            BfsDelete(step->ChildList()[i], path);
            }
        }
        return;
    }
public:
    Folder(string path){
        this->NodePath = path;
        int lastSlashPos = path.find_last_of('/'); // 查找最後一個斜杠的位置
        if (lastSlashPos != string::npos) {
            this->NodeName = path.substr(lastSlashPos + 1); // 提取最後一個斜杠之後的部分
        } else {
            this->NodeName = path;
        }
    }

    void add(Node * node){
        int lastSlashPos = node->path().find_last_of('/');
        string nodeFolder = node->path().substr(0,lastSlashPos);
        if(nodeFolder == NodePath)Children.push_back(node);
        else throw "exception";
    }

    void remove(string path){
        BfsDelete(this, path);
    }

    void removeChild(string path){
        for(int i = 0; i < Children.size(); i++){
            if(Children[i]->path() == path){
                Children.erase(Children.begin()+i);
            }
        }
    }
    
    Node * getChildByName(const char * name) const{
        for(int i = 0; i < Children.size(); i++){
            if(strcmp(name, Children[i]->name().c_str())==0){
                return Children[i];
            }
        }
        return nullptr;
    }

    Node * find(string path){
        DfsIterator it(this);
        while(!it.isDone()){
            if(it.currentItem()->path()==path) return it.currentItem();
            it.next();
        }
        return nullptr;
    }

    int numberOfFiles() const{
        int number=0;
        for(int i = 0; i < Children.size(); i++){
            number += Children[i]->numberOfFiles();
        }
        return number;
    }

    Iterator * createIterator(){
        tmp = new FolderIterator(this);
        return tmp;
    }
};


#endif // FOLDER
