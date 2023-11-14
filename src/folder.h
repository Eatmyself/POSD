#pragma once 

#include <list>
#include <sys/stat.h>
#include "node.h"
#include "iterator.h"

using namespace std;

class Folder: public Node {
private:
    list<Node *> _nodes;
    int _operationCount = 0;

protected:
    void removeChild(Node * target) override {
        _nodes.remove(target);
        _operationCount++;
    }

public:
    Folder(string path): Node(path) {
        struct stat fileInfo;
        const char *c = path.c_str();
        if(lstat(c, &fileInfo) == 0){
            if(S_ISDIR(fileInfo.st_mode))
                return;
        }
        throw "No Folder exists";
    }

    void add(Node * node) override {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
        }
        _nodes.push_back(node);
        node->parent(this);
        _operationCount++;
    }

    Node * getChildByName(const char * name) const override {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }

        return nullptr;
    }

    int numberOfFiles() const override {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    Iterator * createIterator() override {
        return new FolderIterator(this, _operationCount);
    }

    Iterator* createIterator(OrderBy orderBy) override{
        if (orderBy == OrderBy::Normal) {
            return new FolderIterator(this, _operationCount);
        } else if (orderBy == OrderBy::Name) {
            return new OrderByNameIterator(this, _operationCount);
        } else if (orderBy == OrderBy::NameWithFolderFirst) {
            return new OrderByNameWithFolderFirstIterator(this, _operationCount);
        } else if (orderBy == OrderBy::Kind) {
            return new OrderByKindIterator(this, _operationCount);
        } else {
            throw "createIterator error";
        }
    }

    Node * find(string path) override {
        if (this->path() == path) {
            return this;
        }

        size_t index = path.find(this->path());

        if (string::npos == index) {
            return nullptr;
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            Node * result = (*it)->find(path);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            std::list<string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++)
            {
                pathList.push_back(*i);  
            }
        }

        return pathList;
    }

    void remove(string path) override {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }

    void accept(Visitor * visitor) override {
        visitor->visitFolder(this);
    }

    class FolderIterator : public Iterator {
    public:
        FolderIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {}

        ~FolderIterator() {}

        void first() {
            checkAvailable();
            _current = _host->_nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _host->_nodes.end();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByNameIterator: public Iterator {
    public:
        OrderByNameIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {
            for (auto it = _host->_nodes.begin(); it != _host->_nodes.end(); ++it){
                _itnode.push_back(*it);
            }
            _itnode.sort([](Node* a, Node* b){
                return a->name() < b->name();
            });
        }

        ~OrderByNameIterator() {}

        void first() {
            checkAvailable();
            _current = _itnode.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _itnode.end();
        }

    private:
        Folder* const _host;
        list<Node *> _itnode;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    
    };

    class OrderByNameWithFolderFirstIterator: public Iterator {
    public:
        OrderByNameWithFolderFirstIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {
            for (auto it = _host->_nodes.begin(); it != _host->_nodes.end(); ++it){
                _itnode.push_back(*it);
            }
            _itnode.sort([](Node* a, Node* b){
                if (Folder* folder = dynamic_cast<Folder*>(a)){
                    if (File* file = dynamic_cast<File*>(b)) return true;
                    else return a->name() < b->name();
                } 
                else{
                    if(Folder* folder = dynamic_cast<Folder*>(b)) return false;
                    else return a->name() < b->name();
                }
            });
        }

        ~OrderByNameWithFolderFirstIterator() {}

         void first() {
            checkAvailable();
            _current = _itnode.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _itnode.end();
        }

    private:
        Folder* const _host;
        list<Node *> _itnode;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    
    };

    class OrderByKindIterator: public Iterator {
    public:
        OrderByKindIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {
            for (auto it = _host->_nodes.begin(); it != _host->_nodes.end(); ++it){
                _itnode.push_back(*it);
            }
            _itnode.sort([](Node* a, Node* b){
                string Aname;
                string Bname;
                if (Folder* folder = dynamic_cast<Folder*>(a)){
                    Aname = "folder." + a->name();
                }
                else{
                    size_t lastDotPos = a->name().find_last_of('.');
                    if (lastDotPos != std::string::npos) {
                        string extension = a->name().substr(lastDotPos + 1); // 提取最後一個點號之後的部分
                        Aname = extension + "." + a->name();
                    } else {
                        Aname = "file." + a->name();
                    }
                }
                if (Folder* folder = dynamic_cast<Folder*>(b)){
                    Bname = "folder." + Bname;
                }
                else{
                    size_t lastDotPos = b->name().find_last_of('.');
                    if (lastDotPos != std::string::npos) {
                        string extension = b->name().substr(lastDotPos + 1); // 提取最後一個點號之後的部分
                        Bname = extension + "." + b->name();
                    } else {
                        Bname = "file." + b->name();
                    }
                }
                return Aname<Bname;
            });
        }

        ~OrderByKindIterator() {}

        void first() {
            checkAvailable();
            _current = _itnode.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _itnode.end();
        }


    private:
        Folder* const _host;
        list<Node *> _itnode;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    
    };
};
