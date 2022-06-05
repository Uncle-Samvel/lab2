cmake_minimum_required(VERSION 3.16.3)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        lab2
        main.cpp
        myDynamicArray.cpp
        myArraySequence.cpp
        myLinkedList.cpp
        myListSequence.cpp
        myPolynomial.cpp
        menu.cpp menu.h tests.cpp tests.h)