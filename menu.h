#ifndef LAB2_MENU_H
#define LAB2_MENU_H

#include <complex>
#include "myPolynomial.h"
#include <iostream>
#include "tests.h"

void mainMenu();
int getType();

//1
void readPolynomial(myArraySequence<myPolynomial<int>*> *intArr,
                    myArraySequence<myPolynomial<float>*> *floatArr,
                    myArraySequence<myPolynomial<std::complex<int>>*> *complexArr);

template<class T>
void readTypePolynomial(myArraySequence<myPolynomial<T>*> *arr, int count);

template<class T>
void generateRandomPolynomial(myArraySequence<myPolynomial<T>*> *arr, int count, T (*func)());

//2
void operationWithPolynomial(myArraySequence<myPolynomial<int>*> *intArr,
                             myArraySequence<myPolynomial<float>*> *floatArr,
                             myArraySequence<myPolynomial<std::complex<int>>*> *complexArr);

template<class T>
void operationTypeWithPolynomial(myArraySequence<myPolynomial<T>*> *arr);

//3
void printPolynomial(myArraySequence<myPolynomial<int>*> *intArr,
                     myArraySequence<myPolynomial<float>*> *floatArr,
                     myArraySequence<myPolynomial<std::complex<int>>*> *complexArr);

template<class T>
void printTypePolynomial(myArraySequence<myPolynomial<T>*> *arr);


//4
void deletePolynomial(myArraySequence<myPolynomial<int>*> *intArr,
                      myArraySequence<myPolynomial<float>*> *floatArr,
                      myArraySequence<myPolynomial<std::complex<int>>*> *complexArr);

template<class T>
void deleteTypePolynomial(myArraySequence<myPolynomial<T>*> *arr);

//5
void testFunc();

#endif //LAB2_MENU_H
