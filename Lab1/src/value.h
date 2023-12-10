#pragma once

#include <string>
#include "json_iterator.h"
#include "visitor.h"

using namespace std;
class Value {
    public:
        virtual string toString() const=0;
        virtual JsonIterator * createIterator()=0;
        virtual void accept(JsonVisitor * visitor)=0;
};