#pragma once

#include <string>
#include <dirent.h>
#include <sys/stat.h>

using std::string;

class FileSystemScanner {
private:
    DIR* directory;
    struct dirent* dirEntry;
    string _currentnode;
    string _path;
public:
    FileSystemScanner() : directory(nullptr), dirEntry(nullptr) {}

    bool isFile(){
        return dirEntry != nullptr && (dirEntry->d_type != DT_DIR);
    }

    bool isFolder(){
        return dirEntry != nullptr && (dirEntry->d_type == DT_DIR);
    }

    bool isDone(){
        return directory == nullptr || dirEntry == nullptr;
    }

    void setPath(string path){
        _path = path;
        directory = opendir(path.c_str());
        if (directory == nullptr) {
            throw "path error";
        }
    }

    string currentNodeName(){
        return _currentnode;
    }

    void nextNode(){
        if (directory == nullptr) {
            return;
        }

        dirEntry = readdir(directory);
        if (dirEntry == nullptr) {
            return;
        }

        string nodeName = dirEntry->d_name;
        if (nodeName != "." && nodeName != ".." && nodeName[0]!='.'){
            _currentnode = _path + "/" + nodeName;
            return;
        }

        return nextNode(); // Skip "." and ".."
    }
};
