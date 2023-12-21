#pragma once

#include "node.h"
#include "visitor.h"

class File: public Node {
public:
    File(string path): Node(path) {
        struct stat fileInfo;
        const char *c = path.c_str();
        if(lstat(c, &fileInfo) == 0){
            if(S_ISREG(fileInfo.st_mode))
                return;
        }
        throw "No File exists";
    }

    void rename(string name) override{
        if(parent()!=nullptr) _path = parent()->path() + "/" + name;
        else{
            size_t slash = _path.rfind("/");
            _path = _path.substr(0,slash+1) + name;
        }
    }
    
    int numberOfFiles() const override {
        return 1;
    }

    Node * find(string path) override {
        if (this->path() == path) {
            return this;
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }
        return pathList;
    }

    void accept(Visitor * visitor) override {
        visitor->visitFile(this);
    }
};
