#ifndef LAB2_MYPOLYNOMIAL_H
#define LAB2_MYPOLYNOMIAL_H

#include <iostream>
#include "myArraySequence.h"



template<class T>
class myPolynomial {
private:
    myArraySequence<T> elements;
    std::string symbol = "x";

    static T sumElem(T item1, T item2) {
        return item1 + item2;
    }

    static T sumArr(myArraySequence<T> array) {
        return array.reduce(sumElem);
    }

    static T subElem(T item1, T item2) {
        return item1 - item2;
    }

    static T subArr(myArraySequence<T> array) {
        return array.template reduce(subElem);
    }

    static T multElem(T item1, T item2) {
        return item1 * item2;
    }

    static T multArr(myArraySequence<T> array) {
        return array.template reduce(multElem);
    }

public:
    friend std::ostream &operator << (std::ostream &cout, myPolynomial<T> polynomial) {
        int count = 0;
        for (int i = polynomial.elements.length() - 1; i >= 0; i--) {
            if (polynomial.elements[i] == 0) continue;
            count++;
            cout << '(' << polynomial.elements[i] << ')';
            if (i != 0) {
                cout << '*';
                if (polynomial.symbol.length() == 1)
                    cout << polynomial.symbol;
                else
                    cout << "\"" << polynomial.symbol << "\"";
                cout << '^' << i;
            }
            cout << " + ";
        }
        if (count == 0) cout << '(' << (T) 0 << ')';
        else cout << "\b\b\b";
        return cout;
    }

    explicit myPolynomial(myArraySequence<T> &arraySequence) : elements(myArraySequence<T>(arraySequence)) {
        checkLength();
    };

    explicit myPolynomial(T item) : elements(myArraySequence<T>(item)) {
        checkLength();
    };

    myPolynomial() : elements(myArraySequence<T>()) {
        checkLength();
    };

    myPolynomial(const myPolynomial<T> &polynomial) : elements(polynomial.elements), symbol(polynomial.symbol) {
        checkLength();
    };

    T get(int index) {
        return elements[index];
    }

    myPolynomial<T> setSymbol(const std::string& str) {
        if (str.length() != 0)
            symbol = str;
        return *this;
    }

    std::string getSymbol() {
        return symbol;
    }

    void checkLength() {
        int i;
        for (i = elements.length() - 1; i > 0 && elements[i] == 0; i--);
        i++;
        if (i != elements.length())
            elements.remove(i);
    }

    int length() {
        return elements.length();
    }

    T &operator[](int index) {
        return elements[index];
    }

    myPolynomial<T> add(myPolynomial<T> polynomial) {
        auto *arrZip = elements.zip(&polynomial.elements);
        myArraySequence<T> *arrRes = arrZip->map(sumArr);

        delete arrZip;

        for (int i = arrRes->length(); i < elements.length(); i++) {
            arrRes->append(elements[i]);
        }

        for (int i = arrRes->length(); i < polynomial.elements.length(); i++) {
            arrRes->append(polynomial.elements[i]);
        }

        elements = *arrRes;
        delete arrRes;
        /*
        for (int i = 0; i < polynomial.elements.length() && i < elements.length(); i++) {
            elements[i] += polynomial[i];
        }

        for (int i = elements.length(); i < polynomial.elements.length(); i++) {
            elements.append(polynomial[i]);
        }
         */
        checkLength();
        return *this;
    }

    myPolynomial<T> operator+(myPolynomial<T> polynomial) {
        return myPolynomial<T>(*this).add(polynomial);
    }

    myPolynomial<T> operator += (myPolynomial<T> polynomial) {
        return add(polynomial);
    }

    myPolynomial<T> operator+() {
        return myPolynomial<T>(*this);
    }
    /**/
    myPolynomial<T> sub(myPolynomial<T> polynomial) {
        auto *arrZip = elements.zip(&polynomial.elements);
        myArraySequence<T> *arrRes = arrZip->map(subArr);

        delete arrZip;

        for (int i = arrRes->length(); i < elements.length(); i++) {
            arrRes->append(elements[i]);
        }

        for (int i = arrRes->length(); i < polynomial.elements.length(); i++) {
            arrRes->append(0 - polynomial.elements[i]);
        }

        elements = *arrRes;
        delete arrRes;
        checkLength();
        /*
        for (int i = 0; i < polynomial.elements.length() && i < elements.length(); i++) {
            elements[i] -= polynomial.elements[i];
        }

        for (int i = elements.length(); i < polynomial.elements.length(); i++) {
            elements.append(0 - polynomial.elements[i]);
        }
         */
        return *this;
    }

    myPolynomial<T> operator-(myPolynomial<T> polynomial1) {
        return myPolynomial<T>(*this).sub(polynomial1);
    }

    myPolynomial<T> operator -= (myPolynomial<T> polynomial) {
        return sub(polynomial);
    }

    myPolynomial<T> operator-() {
        return myPolynomial<T>().sub(*this);
    }

    myPolynomial<T> mult(myPolynomial<T> polynomial) {
        myPolynomial<T> res;
        myPolynomial<T> pol;
        for (int i = 0; i < polynomial.elements.length(); i++) {
            auto *arr = elements.map(polynomial.elements[i], multElem);
            pol.elements = *arr;
            pol.changeDegree(i);
            res += pol;
            delete arr;
        }

        elements = res.elements;
        checkLength();
        /*
        auto result = myPolynomial<T>();
        for (int i = 0; i < elements.length(); i++) {
            for (int j = 0; j < polynomial.elements.length(); j++) {
                T elem = elements[i] * polynomial.elements[j];
                int index = i + j;
                if (result.elements.length() <= index) {
                    result.elements.append(elem);
                    continue;
                }
                result.elements[index] += elem;
            }
        }
        elements = result.elements;
         */
        return *this;
    }

    myPolynomial<T> operator*(myPolynomial<T> polynomial) {
        return myPolynomial<T>(*this).mult(polynomial);
    }

    myPolynomial<T> operator *= (myPolynomial<T> polynomial) {
        return mult(polynomial);
    }

    myPolynomial<T> scalarMult(T item) {
        auto *arr = elements.map(item, multElem);
        elements = *arr;
        delete arr;
        /*
        for (int i = 0; i < elements.length(); i++) {
            elements[i] *= item;
        }
         */
        checkLength();
        return *this;
    }

    myPolynomial<T> operator*(T item) {
        return myPolynomial<T>(*this).scalarMult(item);
    }

    myPolynomial<T> operator *= (T item) {
        return scalarMult(item);
    }

    myPolynomial<T> *changeDegree(int delta) {
        if (delta == 0) return this;
        if (delta > 0) {
            myArraySequence<T> res;
            for (int i = 0; i < delta; i++) {
                res.append((T) 0);
            }
            res.concat((mySequence<T>*) &elements);
            elements = res;
        }
        else {
            delta *= -1;
            if (delta >= elements.length()) {
                elements.remove();
                return this;
            }
            auto *res = elements.getSubSequence(delta, elements.length());
            elements = *res;
            delete res;
        }
        checkLength();
        return this;
    }

    int operator == (myPolynomial<T> polynomial) {
        checkLength();
        polynomial.checkLength();
        if (elements.length() != polynomial.elements.length()) return 0;

        for (int i = 0; i < elements.length(); i++) {
            if (elements[i] != polynomial.elements[i])
                return 0;
        }

        return 1;
    }

    int operator != (myPolynomial<T> polynomial) {
        return !(*this == polynomial);
    }

    int operator == (T value) {
        if (elements.length() == 1 && elements[0] == value) return 1;

        if (elements.length() == 0 && value == 0) return 1;

        return 0;
    }

    int operator != (T value) {
        return !(*this == value);
    }

    myPolynomial<T> *changeDegree_(int delta) {
        auto *res = new myPolynomial<T>(*this);
        return res->changeDegree(delta);
    }

    myPolynomial<T> pow_(int degree) {
        auto res = myPolynomial<T>(*this);
        auto p = res;
        for (int i = 1; i < degree; i++) {
            res *= p;
        }
        return res;
    }

    T getValue(T item) {
        T res = elements[0];
        for (int i = 1; i < elements.length(); i++) {
            if (elements[i] == 0) continue;
            T val = item;
            for (int j = 1; j < i; j++)
                val *= item;

            res += val * elements[i];
        }

        return res;
    }

    T operator () (T item) {
        return myPolynomial<T>(*this).getValue(item);
    }

    myPolynomial<T> getValue(myPolynomial<T> polynomial) {
        auto res = myPolynomial<T>(elements[0]);
        for (int i = 1; i < elements.length(); i++) {
            res += polynomial.pow_(i) * elements[i];
        }
        res.symbol = polynomial.symbol;
        return res;
    }

    myPolynomial<T> operator () (myPolynomial<T> polynomial) {
        return myPolynomial<T>(*this).getValue(polynomial);
    }

    myPolynomial<T> &operator = (const myPolynomial<T> &polynomial) {
        elements = polynomial.elements;
        return *this;
    }

    myPolynomial<T> map (T value, T (*func)(T value1, T value2)) {
        for (auto &i : elements) {
            i = func(i, value);
        }
        return *this;
    }

    myPolynomial<T> map(myPolynomial<T> polynomial, T (*func)(T value1, T value2)) {
        for (int i = 0; i < elements.length() && i < polynomial.elements.length(); i++) {
            elements[i] = func(elements[i], polynomial[i]);
        }

        return *this;
    }
};

#endif //LAB2_MYPOLYNOMIAL_H
