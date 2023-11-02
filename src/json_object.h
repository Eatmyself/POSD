#pragma once

#include "value.h"
#include <vector>

using namespace std;
class JsonObject : public Value {
    private:
        vector<string> Key;
        vector<Value *> Val;
    public:
        JsonObject() {}

        void set(string s, Value * v){
            for(int i=0;i<Key.size();i++){
                if(Key[i]==s){
                    Val[i] = v;
                    return;
                }
            }
            Key.push_back(s);
            Val.push_back(v);
        }

        Value * getValue(string s) const {
            for(int i=0;i<Key.size();i++){
                if(Key[i]==s){
                    return Val[i];
                }
            }
            throw "exception";
        }

        string toString() const{
            string all="{\n";
            for(int i=0;i<Key.size();i++){
                all+="\"";
                all+=Key[i];
                all+="\"";
                all+=":";

                all+=Val[i]->toString();
                if(i+1<Key.size()){
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
                int n;
                JsonObject * v;
            public:
                JsonObjectIterator(JsonObject * val): v(val) {
                    n=0;
                }
                void first(){
                    n=0;
                }

                string currentKey() const{
                    if(!isDone()) return v->Key[n];
                    else return nullptr;
                }

                Value * currentValue() const{
                    if(!isDone()) return v->Val[n];
                    else return nullptr;
                }

                void next(){
                    if(!isDone()) n++;
                }
                bool isDone() const{
                    if(n+1<=v->Key.size())return false;
                    else return true;
                }
        };
};