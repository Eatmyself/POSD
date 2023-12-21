#pragma once

#include<string>

class Value;

class JsonIterator {
public:
    virtual void first() = 0;

    virtual std::string currentKey() const = 0;

    virtual Value * currentValue() const = 0;

    virtual void next() = 0;
    virtual bool isDone() const = 0;
};

class NullIterator : public JsonIterator {
    void first(){}

    std::string currentKey() const{throw "exception";}

    Value * currentValue() const{throw "exception";}

    void next(){}
    bool isDone() const{return true;}
};