#if !defined(NULL_ITERATOR_H)
#define NULL_ITERATOR_H

#include "iterator.h"

using namespace std;

class NullIterator : public Iterator {
    private:
        Node * ptr;
    public:
        NullIterator(){
            this->ptr=nullptr;
        }
        void first(){}
        Node * currentItem() const{
            return ptr;
        }
        void next(){}
        bool isDone() const{
            return true;
        }
};

#endif // NULL_ITERATOR_H
