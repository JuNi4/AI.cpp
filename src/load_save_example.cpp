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