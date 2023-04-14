# AI.cpp
A "simple" library for creating AIs

## How To Use

It is very simple to use this library. All you have to do, is to install and include the library. Then simply create a neural network object and specify the sizes for the layers. The first layer will always be the input layer. The last layer will always be the output layer. After you have created a neural network, simply call the 'predict' function of the neural network ang give it the inputs in form of a std::vector<double>. This function will then return the output of the neural network in matrix from.

## Note:
1. The neural network, although fast with smaller ones, will take time to process when the amount of neurons are high. It will also consume a lot of RAM, so do not make it bigger than necessary. It will easly consume 16 GB or more at 2 million neurons. Be carefull!

2. Currently, neural networks can't be saved or loaded. But this feature is planned.

## Example:
```cpp
// This will create a neural network with random weights. It will then make a prediction and print the result.

#include "nn/neuralnetwork.h" // includes the nerual network library
#include <iostream>

// a function for getting the current microseconds
#include <chrono>
uint64_t timeSinceEpochMicrosec() {
    using namespace std::chrono;
    return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

int main() {
    // gets the time at wich the programm is started, used for calculating how long the programm took to execute
    double start = timeSinceEpochMicrosec();

    // setup a neural network //
    // the sizes of the layers, the neural network will have 2 input neurons, 5 neurons on a hidden layer and 10 output neurons. 
    std::vector<int> sizes = {2,5,10};
    
    // create the neural network object
    nn::neuralnetwork network(sizes, &nn::sigmoid_activation);

    // create the input vector used for the prediction
    std::vector<std::vector<double>> inputs = { {-1,1} };
    // make a prediction based on the inputs vector and print it
    std::cout << network.predict( cmath::matrix( inputs ) ).str() << "\n";

    // print the time it took to execute the programm
    std::cout << "end of programm, took " << timeSinceEpochMicrosec()-start << " Microseconds\n";
    return 0;
}
```
