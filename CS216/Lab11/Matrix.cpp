/* File: Matrix.cpp
 * Course: CS216-00x
 * Project: Project 3
 * Purpose: the implementation of member functions for the Matrix class.
 *          it represents a undirected graph;
 *          it uses adjacency matrix representation (store 0 if no edge exists; store non-zero value(weight) if an edge exists)
 *
 */
#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "Matrix.h"
#include <cassert>
#include <iostream>

using namespace std;

// constructor
template<class T>
Matrix<T>::Matrix(int sizeX, int sizeY, T initValue) :
dx(sizeX), dy(sizeY)
{
    assert(sizeX > 0 && sizeY > 0);
    for (int i = 0; i < dx; i++)
    {
        vector<T> temp;
        for (int j = 0; j < dy; j++)
            temp.push_back(initValue);
        data.push_back(temp);
    }
}

//operator overloading
template<class T>
T &Matrix<T>::operator()(int x, int y)
{
    assert(x >= 0 && x < dx && y >= 0 && y < dy);
    return this->data[x][y];
}
// << operator overloading
template <class T, class Type>
ostream &operator<<(ostream &out, const Matrix<Type> &m)
{
    out << endl;
    for (int x = 0; x < m.dx; x++)
    {
        for (int y = 0; y < m.dy; y++)
            out << m.data[x][y] << "\t";
        out << endl;
    }
    return out;
}

// binary operator + overloading as friend function
template <class T, class MType>
Matrix<MType> &operator+(const Matrix<MType>& m1, const Matrix<MType>& m2)
{
    assert(m1.dx == m2.dx && m1.dy == m2.dy);
    Matrix<MType> result(m1.dx, m1.dy);
    for (int i = 0; i < m1.dx; i++)
        for (int j = 0; j < m1.dy; j++)
            result(i, j) = m1(i, j) + m2(i, j);
    return result;
}

#endif 
