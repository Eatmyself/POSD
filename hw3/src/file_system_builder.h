#pragma once

#include <string>
#include <stack>

#include "folder.h"
#include "file.h"

using std::string;

class FileSystemBuilder {
private:
    Folder * root;
    std::stack<Node *> _folders;

public:
    FileSystemBuilder() : root(nullptr){}

    Folder * getRoot() const{
        return root;
    }

    void buildFile(string path) {
        if (!_folders.empty()) {
            _folders.top()->add(new File(path));
        }
    }

    void buildFolder(string path){
        Folder* newFolder = new Folder(path);
        if (_folders.empty()) {
            root = newFolder;
            _folders.push(newFolder);
        } else {
            _folders.top()->add(newFolder);
            _folders.push(newFolder);
        }
    }

    void endFolder(){
        if (!_folders.empty()) _folders.pop();
    }

};
