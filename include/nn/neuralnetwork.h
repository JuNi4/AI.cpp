/**
 * @brief Neural Network Library for C++
 *
 * @author JuNi4
 */
// Standard C librarys
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <fstream>
#include <filesystem>
// CMath includes
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

        const char* path_to_file; // the path to the file the neural network got loaded from

        std::string credits = ""; // a variable containing credits from the file the neural network gor loaded from
        std::string description = ""; // a variable containing the description from the file the neural network gor loaded from

    public:
        // public variables
        std::vector<int> sizes;                // the sizes of the layers
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
         * @brief Constructor of the neural network object from a file
         * 
         * @param path The path to a file containing a neural network
         * @param activation_function The activation function for the neuron, see nn::sigmoid_activation
         */
        neuralnetwork(const char* path, double (*activation_function)(double));

        /**
         * @brief Make a prediction based on an input matrix
         * 
         * @param input the input matrix to be processed
         * @return matrix the output matrix containing the prediction
         */
        cmath::matrix predict(cmath::matrix input);

        /**
         * @brief Saves the neural network to the specified file
         * 
         * @param path The path to the file
         */
        void save(const char* path);

        /**
         * @brief Saves the neural network to the same file it got loaded from
         * 
         */
        void save();

};

};

#endif