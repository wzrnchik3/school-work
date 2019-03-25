/* File: Matrix.h
 * Course: CS216-00x
 * Project: Project 3
 * Purpose: the declaration for the Matrix class.
 *          it uses two dimensional vector to store data items 
 *          it is a template class
 *** DO NOT CHANGE THE DECLARATION OF Matrix CLASS ***
 *
 */

#ifndef MATRIX_H
#define	MATRIX_H

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Matrix
{
    public:
        // constructor
        Matrix(int sizeX, int sizeY, T initValue = T());
        int GetSizeX() const { return dx; }
        int GetSizeY() const { return dy; }
        
        // () operator overloading
        T &operator()(int x, int y);

        //for friend function, separate template declaration is needed
        // << operator overloading
        template <class Type>
        friend ostream &operator<<(ostream &out, const Matrix<Type> &m);

        // binary operator + overloading as friend function
        template <class MType>
        friend Matrix<MType> operator+(const Matrix<MType>& m1, const Matrix<MType>& m2);

    private:
        vector<vector<T> > data;
        int dx, dy;
};

#endif	/* MATRIX_H */

#include "Matrix.cpp"
