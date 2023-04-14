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
