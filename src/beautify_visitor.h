#pragma once

#include "visitor.h"
#include "json_object.h"
#include "string_value.h"

class BeautifyVisitor : public JsonVisitor {
private:
    string s="";
public:
    BeautifyVisitor(){}
    void visitJsonObject(JsonObject * obj){
        s+="{\n";
        JsonIterator* it = obj->createIterator();
        while (!(it->isDone()))
        {
            s += "\"" + it->currentKey() + "\": ";
            it->currentValue()->accept(this);
            it->next();
            if(!(it->isDone())){
                s+=",";
            }
            s+="\n";
        }
        s+="}";
    }

    void visitStringValue(StringValue * val){
        s += val->toString();
    }

    string getResult() const{
        return s;
    }
};