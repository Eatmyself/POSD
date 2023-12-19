#pragma once

#include "node.h"
#include "visitor.h"

class Link: public Node {
private:
    Node * _node;
public:
    Link(string path, Node * node): Node(path), _node(node) {}

    void rename(string name) override{
        return _node->rename(name);
    }

    int numberOfFiles() const override {
        return _node->numberOfFiles();
    }

    Node * find(string path) override {
        return _node->find(path);
    }

    std::list<string> findByName(string name) override {
        return _node->findByName(name);
    }

    void accept(Visitor * visitor) override {
        visitor->visitLink(this);
    }

    void add(Node * node) override{
        return _node->add(node);
    }

    void remove(string path) override{
        return _node->remove(path);
    }

    Node * getChildByName(const char * name) const override{
        return _node->getChildByName(name);
    }

    Node * getTarget(){
        return _node;
    }
};
