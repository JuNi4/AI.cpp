#include "matrices.h"
#include "CMathErrors.h"

namespace cmath {

// internal things only used for things inside CMath
namespace internal {

double mathOperator(double a, double b, const char* type) {
    // add the two variables
    if ( type == "+" ) {
        return a + b;
    } else if ( type == "-" ) {
        return a - b;
    } else if ( type == "*" ) {
        return a * b;
    } else if ( type == "/" ) {
        return a / b;
    } else if ( type == "**") {
        return pow(a,b);
    }

    return 0;
}

matrix matrixMathOperator(matrix a, matrix b, const char* type) {   
    // return matrix
    matrix outMat = matrix(a.mat);
    // check if the two matrices are the same size
    int bWidth = b.width;
    int bHeight = b.height;

    int aWidth = a.width;
    int aHeight = a.height;

    // check if sizes are same of multiple of each other
    bool compatible = false;

    const char* variant = "none";

    // check if sizes are the same
    if ( (bWidth == aWidth) && (bHeight == aHeight) ) { compatible = true; variant = "standard"; }
    // check if the sizes are multiples of each other
    else if ( aWidth % bWidth == 0 && aHeight % bHeight == 0 ) { compatible = true; variant = "multiple"; }
    // alternativ mode
    else if ( aHeight % bWidth == 0 && aWidth % bHeight == 0 ) { compatible = true; variant = "multiple2"; }

    // crash if sizes aren't compatible
    if ( !compatible ) {
        printf(CMATH_MATRIX_NOT_SAME_SIZE, aWidth, aHeight, bWidth, bHeight);
        exit(1);
    }

    // the standard mode
    if ( variant == "standard" ) {
        // add two matrices
        for (int h = 0; h < aHeight; h++) {
        for (int w = 0; w < aWidth; w++) {
            // add value to other value
            outMat.mat[h][w] = internal::mathOperator( outMat.mat[h][w], b.mat[h][w], type );
        }
        }
    // the mode when some things are a certain way
    } else if ( variant == "multiple" ) {
        // add two matrices
        int x = 0, y = 0;
        for (int h = 0; h < aHeight; h++) {
        for (int w = 0; w < aWidth; w++) {
            // add value to other value
            outMat.mat[h][w] = internal::mathOperator( outMat.mat[h][w], b.mat[y][x], type );
            x++;
            if ( x >= b.width) { x = 0; }
        }
        y++;
        if ( y >= b.height) { y = 0; }
        }
    //  when certain things are another way
    } else if ( variant == "multiple2" ) {
        // add two matrices
        int x = 0, y = 0;
        for (int w = 0; w < aWidth; w++) {
        for (int h = 0; h < aHeight; h++) {
            // add value to other value
            outMat.mat[h][w] = internal::mathOperator( outMat.mat[h][w], b.mat[x][y], type );
            x++;
            if ( x >= b.width) { x = 0; }
        }
        y++;
        if ( y >= b.height) { y = 0; }
        }
    }

    // return output matrix
    return outMat;
}

};

//////////////////
// Constructors //
//////////////////

matrix::matrix(int width, int height, double default_value) {
    // construct matrix
    this->width = width;
    this->height = height;
    this->mat = std::vector<std::vector<double>>(height);
    // width var
    std::vector<double> x(width);
    for (int i = 0; i < width; i++) {
        x[i] = default_value;
    }
    // add width vectors
    for (int i = 0; i < this->height; i++) {
        this->mat[i] = x;
    }
}

matrix::matrix(std::vector<int> size, double default_value) {
    // construct matrix
    this->width = size[0];
    this->height = size[1];
    this->mat = std::vector<std::vector<double>>(this->height);
    // width var
    std::vector<double> x(this->width);
    for (int i = 0; i < this->width; i++) {
        // add 0 to row vector
        x[i] = default_value;
    }
    // add width vectors
    for (int i = 0; i < this->height; i++) {
        // add row vector to matrix
        this->mat[i] = x;
    }
}

matrix::matrix(std::vector<std::vector<double>> mat) {
    // construct matrix
    this->width = mat[0].size();
    this->height = mat.size();
    this->mat = std::vector<std::vector<double>>(height);
    // add width vectors
    for (int i = 0; i < this->height; i++) {
        this->mat[i] = std::vector<double>(width);
    }

    // set the values of the matrix from mat var
    for (int h = 0; h < mat.size(); h++) {
    for (int w = 0; w < mat[h].size(); w++) {
        // set data in matrix
        this->mat[h][w] = mat[h][w];
    }
    }
}

/////////////////////////////
// operators with matrices //
/////////////////////////////

matrix matrix::operator+(matrix b) {
    return internal::matrixMathOperator(matrix(this->mat), b, "+");
}
void matrix::operator+=(matrix b) {
    this->mat = internal::matrixMathOperator(matrix(this->mat), b, "+").mat;
}

matrix matrix::operator-(matrix b) {
    return internal::matrixMathOperator(matrix(this->mat), b, "-");
}
void matrix::operator-=(matrix b) {
    this->mat = internal::matrixMathOperator(matrix(this->mat), b, "-").mat;
}

matrix matrix::operator*(matrix b) {
    return internal::matrixMathOperator(matrix(this->mat), b, "*");
}
void matrix::operator*=(matrix b) {
    this->mat = internal::matrixMathOperator(matrix(this->mat), b, "*").mat;
}

matrix matrix::operator/(matrix b) {
    return internal::matrixMathOperator(matrix(this->mat), b, "/");
}
void matrix::operator/=(matrix b) {
    this->mat = internal::matrixMathOperator(matrix(this->mat), b, "/").mat;
}

////////////////////////////
// operators with numbers //
////////////////////////////

matrix matrix::operator+(double b) {
    // return matrix
    matrix outMat = matrix(this->mat);

    // perform action to the matrix
    for (int h = 0; h < this->height; h++) {
    for (int w = 0; w < this->width; w++) {
        // perform action to the matrix
        outMat.mat[h][w] += b;
    }
    }

    // return output matrix
    return outMat;
}
void matrix::operator+=(double b) {
    // perform action to the matrix
    for (int h = 0; h < this->height; h++) {
    for (int w = 0; w < this->width; w++) {
        // perform action to the matrix
        this->mat[h][w] += b;
    }
    }
}

matrix matrix::operator-(double b) {
    // return matrix
    matrix outMat = matrix(this->mat);

    // perform action to the matrix
    for (int h = 0; h < this->height; h++) {
    for (int w = 0; w < this->width; w++) {
        // perform action to the matrix
        outMat.mat[h][w] -= b;
    }
    }

    // return output matrix
    return outMat;
}
void matrix::operator-=(double b) {
    // perform action to the matrix
    for (int h = 0; h < this->height; h++) {
    for (int w = 0; w < this->width; w++) {
        // perform action to the matrix
        this->mat[h][w] -= b;
    }
    }
}

matrix matrix::operator*(double b) {
    // return matrix
    matrix outMat = matrix(this->mat);

    // perform action to the matrix
    for (int h = 0; h < this->height; h++) {
    for (int w = 0; w < this->width; w++) {
        // perform action to the matrix
        outMat.mat[h][w] *= b;
    }
    }

    // return output matrix
    return outMat;
}
void matrix::operator*=(double b) {
    // perform action to the matrix
    for (int h = 0; h < this->height; h++) {
    for (int w = 0; w < this->width; w++) {
        // perform action to the matrix
        this->mat[h][w] *= b;
    }
    }
}

matrix matrix::operator/(double b) {
    // return matrix
    matrix outMat = matrix(this->mat);

    // perform action to the matrix
    for (int h = 0; h < this->height; h++) {
    for (int w = 0; w < this->width; w++) {
        // perform action to the matrix
        outMat.mat[h][w] /= b;
    }
    }

    // return output matrix
    return outMat;
}
void matrix::operator/=(double b) {
    // perform action to the matrix
    for (int h = 0; h < this->height; h++) {
    for (int w = 0; w < this->width; w++) {
        // perform action to the matrix
        this->mat[h][w] /= b;
    }
    }
}

// boolean operators

bool matrix::operator==(matrix b) {
    return this->mat == b.mat;
}

/* Theese operators are not posible with matrices
bool matrix::operator>=(matrix b) {

}
bool matrix::operator<=(matrix b) {

}

bool matrix::operator>(matrix b) {

}
bool matrix::operator<(matrix b) {

}
*/

std::string matrix::str() {
    // the variable that will be returned
    std::string out = "";

    // construct the thing
    for ( int i = 0; i < this->height; i++ ) {
        // add line beginning
        out += " [";
        // add elements
        for ( int i2 = 0; i2 < this->width; i2++ ) {
            // add all objects to out
            out += " " + std::to_string( this->mat[i][i2] );
        }
        // add line end
        out += " ],\n";
    }

    out = "[" + out.substr(1,out.size());
    out = out.substr(0,out.size()-2) + "]";

    // return the out var
    return out;
}

};