#pragma once
#include <stack>
#include "json_object.h"

class JsonBuilder {
private:
    JsonObject * root;
    std::stack<JsonObject *> _obj;
    std::stack<std::string> _key;
public:
    JsonBuilder(){
        JsonObject * tmp = new JsonObject;
        root = tmp;
        _obj.push(tmp);
    }
    ~JsonBuilder() {
        delete root;
    }

    void buildValue(std::string key, std::string value){
        Value * v = new StringValue(value);
        _obj.top()->set(key, v);
    }

    void buildObject(std::string key){
        JsonObject * tmp = new JsonObject;
        _obj.push(tmp);
        _key.push(key);
    }

    void endObject(){
        if (!_obj.empty()){
            JsonObject * tmp = _obj.top();
            _obj.pop();
            if (!_obj.empty()){
                _obj.top()->set(_key.top(), tmp);
                _key.pop();
            }
        }
    }

    JsonObject * getJsonObject(){
        return root;
    }
};
