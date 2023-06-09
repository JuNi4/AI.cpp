# AI.cpp
A "simple" library for creating AIs

## How To Use

It is very simple to use this library. All you have to do, is to install and include the library. Then simply create a neural network object and specify the sizes for the layers. The first layer will always be the input layer. The last layer will always be the output layer. Last but not least, the neural network needs an activation function. The library comes with one based on a sigmoid function. To use it, add `&nn::sigmoid_activation` as the last argument for the neural network. After you have created a neural network, simply call the 'predict' function of the neural network ang give it the inputs in form of a std::vector<double>. This function will then return the output of the neural network in matrix from.

## Note:
1. The neural network, although fast with smaller ones, will take time to process when the amount of neurons are high. It will also consume a lot of RAM, so do not make it bigger than necessary. It will easly consume 16 GB or more at 2 million neurons. Be careful.

## Examples:
### A simple random network
src/main.cpp
```cpp
// This will create a neural network with random weights. It will then make a prediction and print the result.

#include "nn/neuralnetwork.h" // includes the nerual network library
#include <iostream>

// a function for getting the current microseconds
//  - Alessandro Pezzato
//  on <https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets>
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
    
    // create the neural network object with the previusly defined sizes and the default sigmoid avtivation function provided by the neural network library
    nn::neuralnetwork network(sizes, &nn::sigmoid_activation);

    // create the input vector used for the prediction
    std::vector<std::vector<double>> inputs = { {-1,1} };
    // make a prediction based on the inputs vector and print it
    std::cout << network.predict( cmath::matrix( inputs ) ).str() << "\n";

    // print the time it took to execute the programm
    std::cout << "end of programm, took " << timeSinceEpochMicrosec()-start << " microseconds\n";
    return 0;
}
```
### Loading and saving a neural network
src/load_save_example.cpp
```cpp
// This will load a network. It will then make a prediction and print the result. After that, this will save the neural network.

#include "nn/neuralnetwork.h" // includes the nerual network library
#include <iostream>

// a function for getting the current microseconds
//  - Alessandro Pezzato
//  on <https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets>
#include <chrono>
uint64_t timeSinceEpochMicrosec() {
    using namespace std::chrono;
    return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

int main() {
    // gets the time at wich the programm is started, used for calculating how long the programm took to execute
    double start = timeSinceEpochMicrosec();

    // setup a neural network //

    // create the neural network object from the specified file
    //  and the default sigmoid avtivation function provided by the neural network library
    nn::neuralnetwork network("trained_models/example.json", &nn::sigmoid_activation);

    // create the input vector used for the prediction
    std::vector<std::vector<double>> inputs = { {-1,1} };
    // make a prediction based on the inputs vector and print it
    std::cout << network.predict( cmath::matrix( inputs ) ).str() << "\n";

    // when training a neural network, it might be helpfull to save your progress
    //  this will save the neural network to the file it was loaded from
    network.save();

    // print the time it took to execute the programm
    std::cout << "end of programm, took " << timeSinceEpochMicrosec()-start << " microseconds\n";
    return 0;
}

