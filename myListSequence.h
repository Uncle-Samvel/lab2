#ifndef LAB2_MYLISTSEQUENCE_H
#define LAB2_MYLISTSEQUENCE_H

#include "mySequence.h"
#include "myLinkedList.cpp"
#include <iostream>

template <class T>
class myListSequence: mySequence<T> {
private:
    myLinkedList<T> linkedList;
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    class Iterator {
    private:
        myListSequence<T> *list;
        using Iter = typename myLinkedList<T>::Iterator;
        Iter iter;
    public:
        Iterator(): list(nullptr) {};

        explicit Iterator(myListSequence<T> *sequence): list(sequence) {
            iter = Iter(&sequence->linkedList);
        }

        Iterator(myListSequence<T> *sequence, Iter iterator): list(sequence), iter(iterator) {}

        T& operator * () const {
            return *iter;
        }

        Iterator& operator ++ () {
            ++iter;
            return *this;
        }

        int operator == (Iterator iterator) {
            return list == iterator.list && iter == iterator.iter;
        }

        int operator != (Iterator iterator) {
            return !(*this == iterator);
        }

        Iterator& operator = (Iterator iterator) {
            list = iterator.list;
            iter = iterator.iter;
            return *this;
        }

        Iterator begin() const {
            return Iterator(list, iter.begin());
        }

        Iterator end() const {
            return Iterator(list, iter.end());
        }

        void operator () (myListSequence<T> *sequence) {
            list = sequence;
            iter = Iter(&sequence->linkedList);
        }
    };

    Iterator iter;

    friend std::ostream &operator << (std::ostream &cout, myListSequence<T> listSequence) {
        return cout << listSequence.linkedList;
    }

    friend std::ostream &operator << (std::ostream &cout, myListSequence<T> *listSequence) {
        return cout << *listSequence;
    }

    myListSequence() {
        linkedList = myLinkedList<T>();
        iter(this);
    }

    myListSequence(T *items, int count) {
        linkedList = myLinkedList<T>(items, count);
        iter(this);
    }

    explicit myListSequence(T item) {
        linkedList = myLinkedList<T>(item);
        iter(this);
    }

    myListSequence(const myListSequence<T> &list) {
        linkedList = list.linkedList;
        iter(this);
    }

    explicit myListSequence(const myLinkedList<T> &list) {
        linkedList = list;
        iter(this);
    }

    T getFirst() {
        if (linkedList.length() == 0) throw IndexOutOfRange(0, 0);
        return linkedList.getFirst();
    }

    T getLast() {
        if (linkedList.length() == 0) throw IndexOutOfRange(0, -1);
        return linkedList.getLast();
    }

    T get(int index) {
        if (index < 0 || index >= linkedList.length()) throw (linkedList.length(), index);
        return linkedList.get(index);
    }

    void set(T item, int index) {
        if (index < 0 || index >= linkedList.length()) throw (linkedList.length(), index);
        linkedList.set(item, index);
    }

    T &operator [] (int index) {
        if (index < 0 || index >= linkedList.length()) throw (linkedList.length(), index);
        return linkedList[index];
    }

    myListSequence<T>& operator = (myListSequence<T> listSequence) {
        linkedList = listSequence.linkedList;
        return *this;
    }

    mySequence<T> *getSubSequence(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= linkedList.length()) throw (linkedList.length(), startIndex);
        if (endIndex < 0 || endIndex >= linkedList.length()) throw (linkedList.length(), endIndex);

        auto *res = new myListSequence<T>(linkedList.getSubList(startIndex, endIndex));
        return res;
    }

    int length() {
        return linkedList.length();
    }

    void append(T item) {
        linkedList.append(item);
    }

    void prepend(T item) {
        linkedList.prepend(item);
    }

    void insert(T item, int index) {
        if (index < 0 || index >= linkedList.length()) throw (linkedList.length(), index);

        linkedList.insert(item, index);
    }

    myListSequence<T> *concat(mySequence<T> *list) {
        for (int i = 0; i < list->length(); i++) {
            linkedList.append(list->get(i));
        }
        return this;
    }

    myListSequence<T> *concat_(mySequence<T> *list) {
        auto *listSequence = new myListSequence<T>(*this);
        for (int i = 0; i < list->length(); i++) {
            listSequence->append(list->get(i));
        }
        return listSequence;
    }

    void reverse() {
        linkedList.reverse();
    }

    int find(T item) {
        return linkedList.find(item);
    }

    int find(mySequence<T> *sequence) {
        myLinkedList<T> list;
        for (int i = 0; i < sequence->length(); i++) {
            list.append(sequence->get(i));
        }
        return linkedList.find(&list);
    }

    myListSequence<myListSequence<T>*>* split(T item) {
        auto res = new myListSequence<myListSequence<T>*>;

        auto *listRes = linkedList.split(item);

        for(auto &i : (*listRes)) {
            res->append(new myListSequence<T>(*i));
        }

        return res;
    }

    Iterator begin() const {
        return iter.begin();
    }

    Iterator end() const {
        return iter.end();
    }

    Iterator operator++() {
        return ++iter;
    }

};


#endif //LAB2_MYLISTSEQUENCE_H
