#if !defined(FILE_H)
#define FILE_H

#include "node.h"
#include "iterator.h"
#include "null_iterator.h"

#include <string>

class File: public Node {
private:
    Iterator * tmp;
public:
    File(string path){
        this->NodePath = path;
        int lastSlashPos = path.find_last_of('/'); // 查找最後一個斜杠的位置
        if (lastSlashPos != string::npos) {
            this->NodeName = path.substr(lastSlashPos + 1); // 提取最後一個斜杠之後的部分
        } else {
            this->NodeName = path;
        }
    }

    void add(Node * node){}

    void remove(string path){}

    Node * getChildByName(const char * name) const{
        return nullptr;
    }

    Node * find(string path){
        return nullptr;
    }

    int numberOfFiles() const{
        return 1;
    }

    Iterator * createIterator(){
        tmp = new NullIterator;
        return tmp;
    }
};

#endif // FILE_H
