#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <sstream>

class StreamOutVisitor : public Visitor {
private:
    string output = "";
public:
    void visitFile(File * file){
        ifstream myFile;
        string line;
        myFile.open(file->path());

        if(output!="") output += "\n";
        output += "_____________________________________________\n";
        output += file->path() + "\n";
        output += "---------------------------------------------\n";
        while (getline(myFile, line)) {
            output += line + "\n";
        }
        output += "_____________________________________________\n";

        myFile.close();
    }

    void visitFolder(Folder * folder){
        Iterator * it = folder->createIterator();
        it->first();
        
        while(!(it->isDone())){
            it->currentItem()->accept(this);
            it->next();
        }
        if(output!="") output += "\n";
    }

    string getResult() const{
        return output;
    }
};