#ifndef LAB2_TESTS_H
#define LAB2_TESTS_H

#include "myDynamicArray.cpp"
#include "myArraySequence.h"
#include "myLinkedList.cpp"
#include "myListSequence.h"
#include "myPolynomial.h"

#include "iostream"
#include "random"

class testFault{
public:
    int done;
    int fault;
    testFault(): done(0), fault(0) {}
    testFault(int done, int fault): done(done), fault(fault) {}
};

void testAll(int count, int print);


void dynamicArrTest(int count, int print);

void dynamicArrTestResize(int count, int print);
void dynamicArrTestGetItem(int count, int print);
void dynamicArrTestReverse(int count, int print);
void dynamicArrTestFind(int count, int print);


void myArraySequenceTest(int count, int print);

void myArraySequenceTestResize(int count, int print);
void myArraySequenceTestGetItem(int count, int print);
void myArraySequenceTestReverse(int count, int print);
void myArraySequenceTestFind(int count, int print);


void myLinkedListTest(int count, int print);

void myLinkedListTestResize(int count, int print);
void myLinkedListTestGetItem(int count, int print);
void myLinkedListTestReverse(int count, int print);
void myLinkedListTestFind(int count, int print);


void myListSequenceTest(int count, int print);

void myListSequenceTestResize(int count, int print);
void myListSequenceTestGetItem(int count, int print);
void myListSequenceTestReverse(int count, int print);
void myListSequenceTestFind(int count, int print);


void myPolynomialTest(int count, int print);

void myPolynomialTestSum(int count, int print);
void myPolynomialTestSub(int count, int print);
void myPolynomialTestMult(int count, int print);
void myPolynomialTestScalar(int count, int print);
void myPolynomialTestPow(int count, int print);

#endif //LAB2_TESTS_H
