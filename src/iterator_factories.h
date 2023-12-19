#pragma once

#include "iterator_factory.h"
#include "order_by.h"

class FolderIteratorFactory: public IteratorFactory {
    static IteratorFactory * instance(){
        if (_instance == nullptr){
            _instance = new FolderIteratorFactory();
        }
        return _instance;
    }

    Iterator * create(Folder * node, int operationCount){
        return new Folder::FolderIterator(node, operationCount);
    }

    private:
        static IteratorFactory * _instance;
};

class OrderByNameIteratorFactory: public IteratorFactory {
    static IteratorFactory * instance(){
        if (_instance == nullptr){
            _instance = new FolderIteratorFactory();
        }
        return _instance;
    }

    Iterator * create(Folder * node, int operationCount){
        return new Folder::OrderByNameIterator(node, operationCount);
    }

    private:
        static IteratorFactory * _instance;
};

class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
    static IteratorFactory * instance(){
        if (_instance == nullptr){
            _instance = new FolderIteratorFactory();
        }
        return _instance;
    }

    Iterator * create(Folder * node, int operationCount){
        return new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
    }

    private:
        static IteratorFactory * _instance;
};

class OrderByKindIteratorFactory: public IteratorFactory {
    static IteratorFactory * instance(){
        if (_instance == nullptr){
            _instance = new FolderIteratorFactory();
        }
        return _instance;
    }

    Iterator * create(Folder * node, int operationCount){
        return new Folder::OrderByKindIterator(node, operationCount);
    }

    private:
        static IteratorFactory * _instance;
};
