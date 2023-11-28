#pragma once

#include "visitor.h"
#include "json_object.h"
#include "string_value.h"

class BeautifyVisitor : public JsonVisitor {
private:
    string s="";
    int num=0;
public:
    BeautifyVisitor(){}
    void visitJsonObject(JsonObject * obj){
        s+="{\n";
        JsonIterator* it = obj->createIterator();
        num++;
        while (!(it->isDone()))
        {   
            for(int i=0;i<num;i++)s+="    ";
            s += "\"" + it->currentKey() + "\": ";
            it->currentValue()->accept(this);
            it->next();
            if(!(it->isDone())){
                s+=",";
            }
            s+="\n";
        }
        num--;
        for(int i=0;i<num;i++)s+="    ";
        s+="}";
    }

    void visitStringValue(StringValue * val){
        s += val->toString();
    }

    string getResult() const{
        return s;
    }
};