/**
 * @file matrices.h
 * @author JuNi4
 * @brief Matrices in C++
 * @date 2023-04-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <vector>

#include <math.h>

#ifndef _CMATH_MATRICES_
#define _CMATH_MATRICES_

namespace cmath {

class matrix {

    public:

    int width, height;

    std::vector<std::vector<double>> mat;

    /**
     * @brief Construct a new matrix object
     * 
     * @param width The width of the matrix
     * @param height The height of the matrix
     */
    matrix(int width, int height, double default_value = 0);
    /**
     * @brief Construct a new matrix object
     * 
     * @param size The size of the matrix
     */
    matrix(std::vector<int> size, double default_value = 0);
    /**
     * @brief Construct a new matrix object with values
     * 
     * @param width The width of the matrix
     * @param height The height of the matrix
     */
    matrix(std::vector<std::vector<double>> mat);

    // operations with matrices
    matrix operator+(matrix b);
    void operator+=(matrix b);

    matrix operator-(matrix b);
    void operator-=(matrix b);

    matrix operator*(matrix b);
    void operator*=(matrix b);

    matrix operator/(matrix b);
    void operator/=(matrix b);

    // operations with numbers
    matrix operator+(double b);
    void operator+=(double b);

    matrix operator-(double b);
    void operator-=(double b);

    matrix operator*(double b);
    void operator*=(double b);

    matrix operator/(double b);
    void operator/=(double b);

    // boolean operators
    bool operator==(matrix b);

    /* Theese operators are not posible with matrices
    bool operator>=(matrix b);
    bool operator<=(matrix b);

    bool operator>(matrix b);
    bool operator<(matrix b);
    */

    /**
     * @brief create a const char* from the matrix
     * 
     */
    std::string str();
};

};

#endif