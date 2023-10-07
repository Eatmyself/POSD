#if !defined(NODE_H)
#define NODE_H

#include<string>

class Iterator;
using namespace std;

class Node {
protected:
    vector<Node *> Children;
    string NodePath;
    string NodeName;
public:
    string name() const{
        return NodeName;
    }
    
    string path() const{
        return NodePath;
    }
    
    vector<Node *> ChildList(){
        return Children;
    }
    
    void add(Node * node);

    void remove(string path);
 
    Node * getChildByName(const char * name) const;

    Node * find(string path);

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() = 0;
};


#endif // NODE_H
