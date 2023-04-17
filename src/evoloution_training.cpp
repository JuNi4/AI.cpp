// This will train a neural network based on the evoloution algorithm
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

#include <nn/neuralnetwork.h>
#include <json.hpp>

#include "dataset/mnist_dataset.hpp"

using json = nlohmann::json;

// the path to the save of the network
const char* save_path = "trained_models/number_recognition.json";

int highest(std::vector<double> inp) {
    // get the highest index
    int highest_v = 0;
    int highest_i = 0;

    for (int i = 0; i < inp.size(); i++) {
        if (inp[i] > highest_v) {
            highest_v = inp[i];
            highest_i = i;
        }
    }

    return highest_i;
}

int getAccuracy( std::vector<std::vector<double>> dataset, std::vector<int> labels, nn::neuralnetwork ai ) {
    // the amount of correct results
    int correct = 0;
    // make a lot of predictions and check if they are correct
    for (int i = 0; i < dataset.size(); i++) {
        std::cout << i << "/" << dataset.size() << "\n";
        // create input matrix
        cmath::matrix input({dataset[i]});
        // make prediction
        cmath::matrix output = ai.predict( input );
        // check if the highest output is the correct answer
        if ( highest(output.mat[0]) == labels[i] ) {
            correct++;
        }
    }
    // return the amount of correct results
    return correct;
}

int main() {
    // create a new neural network
    nn::neuralnetwork ai( {1,1}, &nn::sigmoid_activation );
    if ( std::filesystem::is_regular_file(save_path) ) {
        std::cout << "[Training] Loading network.\n";
        ai = nn::neuralnetwork(save_path, &nn::sigmoid_activation);
    } else {
        std::cout << "[Training] Creating new network.\n";
        ai = nn::neuralnetwork({28*28, 300, 10}, &nn::sigmoid_activation);
    }

    // get dataset
    std::cout << "[Training] Loading dataset.\n";
    json dataset = getDataset();

    json trainingData = dataset["training"];

    // get an initial accuracy
    std::cout << "[Training] Getting initial accuracy.\n";
    int correct = getAccuracy( trainingData["images"], trainingData["labels"], ai);

    std::cout << "[Training] Calculating percantage.\n";
    double startingPercentage = ((float)correct / (float)trainingData["images"].size());

    std::cout << "[Trainig] Initial correct answers: " << correct << "/" << trainingData["images"].size() << " (" << startingPercentage*100 << "%).\n" ;

    // train the network


    std::cout << "[Training] Reached end of programm, saving network...\n";
    // at the end, save the neural network
    ai.save(save_path, -1);

    return 0;
}