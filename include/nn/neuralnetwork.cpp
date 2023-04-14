#include "neuralnetwork.h"
#include <CMath/standardNormalDeviation.hpp>

// Inspired by
// - https://www.youtube.com/watch?v=8bNIkfRJZpo

namespace nn {

double sigmoid_activation(double x) {
    return (double)1./((double)1.+(double)exp(-x)); // return a sigmoid based activation number
}

/////////////////////
// Neural Networks //
/////////////////////

neuralnetwork::neuralnetwork(std::vector<int> sizes, double (*activation_function)(double)) {
    // construct the neural network
    // setup the shapes that the weight matrices will have
    std::vector<std::vector<int>> weight_shapes;
    // create weight shape vectors
    for (int i = 0; i < sizes.size() -1; i++) {
        // create weight shapes
        weight_shapes.push_back({sizes[i], sizes[i+1]});
    }

    // create weight matrices
    for (int i = 0; i < weight_shapes.size(); i++) {
        /*  Set all weights
            - Create Matrix
            - loop over all objects in matrix
        */
        cmath::matrix mx(weight_shapes[i]);
        // loop part
        for (int y = 0; y < mx.mat.size(); y++) {
        for (int x = 0; x < mx.mat[0].size(); x++) {
            // set part to standard normal deviation
            mx.mat[y][x] = (double) cmath::standardNormalDeviation();
        }}

        // add matrix to list of weights
        this->weights.push_back(mx);
    }

    // create biases
    for (int i = 1; i < sizes.size(); i++) {
        // create bais matrix
        cmath::matrix x(1,sizes[i]);
        // add bias matrix to biases
        this->biases.push_back(x);
    }

    // set the activation functions
    this->activation_function = activation_function;
}

cmath::matrix nn::neuralnetwork::predict(cmath::matrix x) {
    // make a prediction
    for (int i = 0; i < this->weights.size(); i++) {
        // do math
        /*
            - Multiply weights with x
            - "collaps" matrix
            - add bias
         */

        cmath::matrix weight(this->weights[i].mat);

        // Multiply weigths with x
        weight *= x;
        // "collaps" matrix
        cmath::matrix collapsed(1,weight.height);
        for (int h = 0; h < weight.height; h++) {
        for (int w = 0; w < weight.width; w++) {
            // "collaps" matrix
            collapsed.mat[h][0] += weight.mat[h][w];
        }
        }

        // set x to the collapsed matrix
        x = collapsed;

        // add bias to the matrix
        x += this->biases[i];

        // the matrix after taking the activation function into account
        cmath::matrix activated(x.mat);

        // add activation function into the mix
        for (int h = 0; h < x.height; h++) {
            activated.mat[h][0] = this->activation_function(x.mat[h][0]);
        }

        // set x to the matrix with activation function
        x = activated;

    }

    // return the output matrix
    return x;
}

};
