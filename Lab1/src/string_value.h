#pragma once

#include "value.h"

using namespace std;
class StringValue : public Value {
    private:
        string s;
    public:
        StringValue(string str): s(str) {}

        string toString() const{
            return "\"" + s + "\"";
        }

        JsonIterator * createIterator() {
            return new NullIterator();
        }

        void accept(JsonVisitor * visitor){
            visitor->visitStringValue(this);
        }
};