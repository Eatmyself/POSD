#pragma once

#include "value.h"
#include <map>

using namespace std;
class JsonObject : public Value {
    private:
        map<string, Value *> _jsonobj;
    public:
        JsonObject() {}

        void set(string s, Value * v){
            _jsonobj[s]=v;
        }

        Value * getValue(string s) const {
            //map<string, Value *>::iterator it;
            auto it = _jsonobj.find(s);
            if (it != _jsonobj.end()) return it->second;
            else throw "exception";
        }

        string toString() const{
            string all="{\n";
            for(auto it=_jsonobj.begin(); it!=_jsonobj.end(); ++it){
                all+="\"";
                all+=it->first;
                all+="\"";
                all+=":";

                all+=it->second->toString();
                if(it != prev(_jsonobj.end())){
                    all+=",";
                }
                all+="\n";
            }
            all+="}";

            return all;
        }

        JsonIterator * createIterator() {
            return new JsonObjectIterator(this);
        }

        void accept(JsonVisitor * visitor){
            visitor->visitJsonObject(this);
        }

        //Iterator
        class JsonObjectIterator : public JsonIterator {
            private:
                map<string, Value *>::iterator it;
                JsonObject * v;
            public:
                JsonObjectIterator(JsonObject * val): v(val) {
                    it = v->_jsonobj.begin();
                }

                ~JsonObjectIterator(){
                    delete v;
                }

                void first(){
                    it = v->_jsonobj.begin();
                }

                string currentKey() const{
                    if(!isDone()) return it->first;
                    else return nullptr;
                }

                Value * currentValue() const{
                    if(!isDone()) return it->second;
                    else return nullptr;
                }

                void next(){
                    if(!isDone()) it++;
                }
                bool isDone() const{
                    if(it!=v->_jsonobj.end())return false;
                    else return true;
                }
        };
};