#if !defined(NODE_H)
#define NODE_H

#include<list>
#include<vector>
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
    
    virtual void add(Node * node) = 0;

    virtual void remove(string path) = 0;
 
    virtual void removeChild(string path) = 0;

    virtual Node * getChildByName(const char * name) const = 0;

    virtual Node * find(string path) = 0;

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() = 0;
};


#endif // NODE_H
