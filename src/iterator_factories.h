#pragma once

#include "iterator_factory.h"
#include "order_by.h"

class FolderIteratorFactory: public IteratorFactory {
    public:
        static FolderIteratorFactory * instance(){
            if (_instance == nullptr){
                _instance = new FolderIteratorFactory();
            }
            return _instance;
        }

        Iterator * create(Folder * node, int operationCount){
            return new Folder::FolderIterator(node, operationCount);
        }

    private:
        static FolderIteratorFactory * _instance;
};
FolderIteratorFactory* FolderIteratorFactory::_instance = nullptr;

class OrderByNameIteratorFactory: public IteratorFactory {
    public:
        static OrderByNameIteratorFactory * instance(){
            if (_instance == nullptr){
                _instance = new OrderByNameIteratorFactory();
            }
            return _instance;
        }

        Iterator * create(Folder * node, int operationCount){
            return new Folder::OrderByNameIterator(node, operationCount);
        }

    private:
        static OrderByNameIteratorFactory * _instance;
};
OrderByNameIteratorFactory* OrderByNameIteratorFactory::_instance = nullptr;


class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
    public:
        static OrderByNameWithFolderFirstIteratorFactory * instance(){
            if (_instance == nullptr){
                _instance = new OrderByNameWithFolderFirstIteratorFactory();
            }
            return _instance;
        }

        Iterator * create(Folder * node, int operationCount){
            return new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
        }

    private:
        static OrderByNameWithFolderFirstIteratorFactory * _instance;
};
OrderByNameWithFolderFirstIteratorFactory* OrderByNameWithFolderFirstIteratorFactory::_instance = nullptr;

class OrderByKindIteratorFactory: public IteratorFactory {
    public:
        static OrderByKindIteratorFactory * instance(){
            if (_instance == nullptr){
                _instance = new OrderByKindIteratorFactory();
            }
            return _instance;
        }

        Iterator * create(Folder * node, int operationCount){
            return new Folder::OrderByKindIterator(node, operationCount);
        }

    private:
        static OrderByKindIteratorFactory * _instance;
};
OrderByKindIteratorFactory* OrderByKindIteratorFactory::_instance = nullptr;
