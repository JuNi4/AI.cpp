/**
 * @brief Neural Network Library for C++
 *
 * @author JuNi4
 */
#include <iostream>
#include <vector>
#include <math.h>
#include <CMath/matrices.h>

#ifndef _NEURALNETWORK_
#define _NEURALNETWORK_

namespace nn {

/**
 * @brief An example activation function for a neuron
 * 
 * @param x the input given to the activation function by the neural network
 * @return double the value given back to the neural network to be further processed
 */
double sigmoid_activation(double x);

class neuralnetwork {
    private:
        // private variables
        double (*activation_function)(double);  // the activation function

    public:
        // public variables
        std::vector<cmath::matrix> weights;    // the weight matrix list
        std::vector<cmath::matrix> biases;     // the bias matrix list

        /**
         * @brief Constructor of the neural network object
         * 
         * @param sizes The layer sizes of the neural network
         * @param activation_function The activation function for the neuron, see nn::sigmoid_activation
         */
        neuralnetwork(std::vector<int> sizes, double (*activation_function)(double));

        /**
         * @brief Make a prediction based on an input matrix
         * 
         * @param input the input matrix to be processed
         * @return matrix the output matrix containing the prediction
         */
        cmath::matrix predict(cmath::matrix input);

};

};

#endif