#ifndef LAB2_MYSEQUENCE_H
#define LAB2_MYSEQUENCE_H
#include <iostream>

template<class T>
class mySequence {
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(int index) = 0;
    virtual void set(T item, int index) = 0;
    virtual T &operator [] (int index) = 0;

    virtual mySequence<T>* getSubSequence(
            int startIndex, int endIndex) = 0;

    virtual int length() = 0;

    virtual void append (T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insert (T item, int index) = 0;

    virtual mySequence<T>* concat (mySequence<T>* sequence) = 0;
    virtual mySequence<T>* concat_(mySequence<T>* sequence) = 0;
    virtual void reverse() = 0;

    virtual int find(T item) = 0;
    virtual int find(mySequence<T> *sequence) = 0;
};

#endif //LAB2_MYSEQUENCE_H
