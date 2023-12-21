#pragma once

#include <string>

#include "folder.h"
#include "file_system_builder.h"
#include "file_system_scanner.h"

using std::string;

class FileSystemParser {
private:
    FileSystemBuilder * _builder;
    FileSystemScanner * _scanner = new FileSystemScanner;
public:
    FileSystemParser(FileSystemBuilder * builder): _builder(builder){}

    Folder * getRoot() const{
        return _builder->getRoot();
    }

    void parse(){
        _scanner->nextNode();
        while (!_scanner->isDone()) {
            if (_scanner->isFolder()) {
                FileSystemParser fsp(_builder);
                fsp.setPath(_scanner->currentNodeName());
                fsp.parse();
                _builder->endFolder();
            }
            else if (_scanner->isFile()) {
                _builder->buildFile(_scanner->currentNodeName());
            }
            _scanner->nextNode();
        }
    }

    void setPath(string path){
        _scanner->setPath(path);
        _builder->buildFolder(path);
    }
};
