// This will train a neural network based on the evoloution algorithm
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

#include <nn/neuralnetwork.h>
#include <json.hpp>

#include <random>

#include "dataset/mnist_dataset.hpp"

using json = nlohmann::json;

// Settings //
#define SAMPLE_SIZE 10000
#define GENERATION_SIZE 10
#define LEARN_RATE 1


// the path to the save of the network
const char* save_path = "trained_models/number_recognition.json";

uint64_t timeSinceEpochNanosec() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
}

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

int getAccuracy( std::vector<std::vector<double>> dataset, std::vector<int> labels, nn::neuralnetwork ai, bool print_progress = true ) {
    // the amount of correct results
    int correct = 0;
    // get the sample size
    int size = dataset.size();
    #ifdef SAMPLE_SIZE
    size = SAMPLE_SIZE;
    #endif
    // make a lot of predictions and check if they are correct
    for (int i = 0; i < size; i++) {
        if (print_progress) {
            std::cout << "[Training] Sample " << i << "/" << size << ".\r";
        }
        // create input matrix
        cmath::matrix input({dataset[i]});
        // make prediction
        cmath::matrix output = ai.predict( input );
        // check if the highest output is the correct answer
        if ( highest(output.mat[0]) == labels[i] ) {
            correct++;
        }
    }
    if (print_progress) {
        std::cout << "[Training] Sample " << size << "/" << size << ".\n";
    }
    // return the amount of correct results
    return correct;
}

double getScore( std::vector<std::vector<double>> dataset, std::vector<int> labels, nn::neuralnetwork ai, bool print_progress = true ) {
    // the amount of correct results
    double correct = 0;
    // get the sample size
    int size = dataset.size();
    #ifdef SAMPLE_SIZE
    size = SAMPLE_SIZE;
    #endif
    // make a lot of predictions and check if they are correct
    for (int i = 0; i < size; i++) {
        if (print_progress) {
            std::cout << "[Training] Sample " << i << "/" << size << ".\r";
        }
        // create input matrix
        cmath::matrix input({dataset[i]});
        // make prediction
        cmath::matrix output = ai.predict( input );
        // check if the highest output is the correct answer
        if ( highest(output.mat[0]) == labels[i] ) {
            correct+= output.mat[0][highest(output.mat[0])];
        }
    }
    if (print_progress) {
        std::cout << "[Training] Sample " << size << "/" << size << ".\n";
    }
    // return the amount of correct results
    return correct;
}


nn::neuralnetwork tweak( nn::neuralnetwork input ) {
    // make a lot of changes

    // weights //
    // calculate the amount of weights
    int size = 0;

    for (int wm = 0; wm < input.weights.size(); wm++) {
        for (int wHeight = 0; wHeight < input.weights[wm].mat.size(); wHeight++) {
            size += input.weights[wm].mat[wHeight].size();
        }
    }

    // make weight amount of changes
    for (int i = 0; i < size; i++) {
        // generate wich weight to change
        srand( timeSinceEpochNanosec() );
        int weightMatrix = rand() % input.weights.size();
        srand( timeSinceEpochNanosec() );
        int matrixY = rand() % input.weights[weightMatrix].mat.size();
        srand( timeSinceEpochNanosec() );
        int matrixX = rand() % input.weights[weightMatrix].mat[matrixY].size();
        // generate the change value
        srand( timeSinceEpochNanosec() );
        float change = ((float)(rand() % 200 + 1) / 100. - 1.) * LEARN_RATE;
        // change the value
        input.weights[weightMatrix].mat[matrixY][matrixX] += change;
    }

    // biases //
    // calculate the amount of biases
    size = 0;

    for (int bm = 0; bm < input.biases.size(); bm++) {
        for (int bHeight = 0; bHeight < input.biases[bm].mat.size(); bHeight++) {
            size += input.biases[bm].mat[bHeight].size();
        }
    }

    // make weight amount of changes
    for (int i = 0; i < size; i++) {
        // generate wich weight to change
        srand( timeSinceEpochNanosec() );
        int biasMatrix = rand() % input.biases.size();
        srand( timeSinceEpochNanosec() );
        int matrixY = rand() % input.biases[biasMatrix].mat.size();
        srand( timeSinceEpochNanosec() );
        int matrixX = rand() % input.biases[biasMatrix].mat[matrixY].size();
        // generate the change value
        srand( timeSinceEpochNanosec() );
        float change = ((float)(rand() % 200 + 1) / 100. - 1.) * LEARN_RATE;
        // change the value
        input.biases[biasMatrix].mat[matrixY][matrixX] += change;
    }

    return input;
}

int main() {
    // create a new neural network
    nn::neuralnetwork ai( {1,1}, &nn::sigmoid_activation );
    if ( std::filesystem::is_regular_file(save_path) ) {
        std::cout << "[Training] Loading network.\n";
        ai = nn::neuralnetwork(save_path, &nn::sigmoid_activation);
    } else {
        std::cout << "[Training] Creating new network.\n";
        ai = nn::neuralnetwork({28*28, 25, 10}, &nn::sigmoid_activation);
    }

    // get dataset
    std::cout << "[Training] Loading dataset.\n";
    json dataset = getDataset();

    json trainingData = dataset["training"];

    std::vector<std::vector<double>> images = trainingData["images"];
    std::vector<std::vector<double>> labels = trainingData["labels"];

    // get an initial accuracy
    std::cout << "[Training] Getting initial accuracy.\n";
    int correct = getAccuracy( images, labels, ai);

    int size = images.size();
    #ifdef SAMPLE_SIZE
    size = SAMPLE_SIZE;
    #endif

    std::cout << "[Training] Calculating initial percantage.\n";
    double startingPercentage = ((float)correct / (float)size);

    std::cout << "[Training] Initial correct answers: " << correct << "/" << size << " (" << startingPercentage*100 << "%).\n" ;

    // train the network //

    int generationCount = 1;

    // - create GENERATION_SIZE amount of networks
    // - make minor tweaks
    // - get performance of networks
    // - take the best performing network and set it as the main network
    // - repeat

    // train loop
    while (true) {
        // a list holding all neural networks
        std::vector<nn::neuralnetwork> networks;
        std::vector<double> scores(GENERATION_SIZE);

        // add main network to generation
        networks.push_back(ai);

        std::cout << "[Training] Creating generation " << generationCount << " with a size of " << GENERATION_SIZE << ".\n";
        // copy the main neural network x times
        for (int i = 0; i < GENERATION_SIZE-1; i++) {
            networks.push_back( tweak(ai) );
        }

        std::cout << "[Training] Started testing for generation "<< generationCount <<".\n";
        // get scores
        for (int i = 0; i < GENERATION_SIZE; i++) {
            std::cout << "[Training] Testing network " << i+1 << "/" << GENERATION_SIZE << ".\n";
            // get accuracy of the current network
            double a = getScore( images,labels, networks[i] );

            std::cout << "[Training] Network " << i+1 << " achieved a score of " << a << ".\n";
            // save the score
            scores[i] = a;
        }

        //std::cout << "[Training] Testing network " << GENERATION_SIZE << "/" << GENERATION_SIZE << ".\n";

        // get the best performing network
        double x = 0;
        int index = 0;

        std::cout << "[Training] Evaluating scores...\n";

        for (int i = 0; i < GENERATION_SIZE; i++) {
            // check if score of network is higher
            if (scores[i] > x) {
                // if so, set index and score
                x = scores[i];
                index = i;
            }
        }

        std::cout << "[Training] Updating main network.\n";

        // set main network to the best performing of the generation
        ai = networks[index];

        if (generationCount % 2 == 0) {
            std::cout << "[Training] Saving network...\n";
            ai.save(save_path,-1);
        }

        generationCount++;

    }

    // end of programm //
    std::cout << "[Training] Reached end of programm, saving network...\n";
    // at the end, save the neural network
    ai.save(save_path, -1);

    std::cout << "[Training] Network saved!\n";

    return 0;
}