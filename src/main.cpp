#include "nn/neuralnetwork.h"
#include <iostream>

#include <chrono>

uint64_t timeSinceEpochMicrosec() {
    using namespace std::chrono;
    return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

int main() {
    // setup a neural network //
    // the sizes of the layers
    std::vector<int> sizes = {2,5,10};
    
    double start = timeSinceEpochMicrosec();
    // create the neural network
    nn::neuralnetwork network(sizes, &nn::sigmoid_activation);

    //predict something
    std::vector<std::vector<double>> inputs = { {-1,1} };
    //network.predict( cmath::matrix( inputs ) );
    std::cout << network.predict( cmath::matrix( inputs ) ).str() << "\n";

    // std::cout <<  << "\n";

    std::cout << "end of programm, took " << timeSinceEpochMicrosec()-start << " Microseconds\n";
    return 0;
}