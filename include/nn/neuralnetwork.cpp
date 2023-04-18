/**
 * @brief Neural Network Library for C++
 *
 * @author JuNi4
 */
#include "neuralnetwork.h"

// CMath librarys
#include <CMath/standardNormalDeviation.hpp>
// json library
#include <json.hpp>

using json = nlohmann::json;

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

    // set the sizes of the neural network
    this->sizes = sizes;

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

neuralnetwork::neuralnetwork(const char* path, double (*activation_function)(double)) {
    // check if file exists
    if (! std::filesystem::is_regular_file(path) ) {
        std::cerr << "Can not open file\n";
        exit(1);
    }
    // save the file path
    this->path_to_file = path;
    // the file contents
    std::string content;
    // load the file
    std::ifstream aiFile (path);

    while (aiFile) {
        content += aiFile.get();
    }

    aiFile.close();

    // load file as json
    json aiData = json::parse(content.substr(0,content.size()-1));

    // save description and credits
    if ( aiData["credits"] != nullptr ) {
        this->credits = aiData["credits"];
    }
    if ( aiData["description"] != nullptr ) {
        this->description = aiData["description"];
    }

    // set the matrix sizes
    this->sizes = (std::vector<int>) aiData["layer_sizes"];

    // set the weights
    for (int i = 0; i < aiData["weights"].size(); i++) {
        // recreate the weight matrix
        cmath::matrix x( (std::vector<std::vector<double>>) aiData["weights"][i] );
        // add the weight matrix to the weight list
        this->weights.push_back(x);
    }

    // set the biases
    for (int i = 0; i < aiData["biases"].size(); i++) {
        // recreate the bias matrix
        cmath::matrix x( (std::vector<std::vector<double>>) aiData["biases"][i] );
        // add the bias matrix to the bias list
        this->biases.push_back(x);
    }

    // set the activation functions
    this->activation_function = activation_function;
}

cmath::matrix nn::neuralnetwork::predict(cmath::matrix x) {
    // check if input matrix has the correct dimensions
    if (!( x.width == this->sizes[0] && x.height == 1 )) {
        std::cerr << "Input matrix for prediction is not the correct size\n";
        exit(1);
    }
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

void neuralnetwork::save(const char* path, int indent) {
    // create the json object
    json out;

    // set description
    if ( this->description != "" ) {
        out["description"] = this->description;
    }
    // set credits
    if ( this->credits != "" ) {
        out["credits"] = this->credits;
    }

    // set sizes
    out["layer_sizes"] = this->sizes;

    // set the bias values
    out["biases"] = {};
    for ( int i = 0; i < this->biases.size(); i++ ) {
        out["biases"].push_back(this->biases[i].mat);
    }

    // set the weight values
    out["weights"] = {};
    for ( int i = 0; i < this->weights.size(); i++ ) {
        out["weights"].push_back(this->weights[i].mat);
    }

    if (! std::filesystem::is_regular_file(path) ) {

    }

    // open file
    std::ofstream aiFile(path);
    // save json to file
    if (indent >= 0) {
        aiFile << out.dump(indent).c_str();
    } else {
        aiFile << out.dump().c_str();
    }
    // close the file
    aiFile.close();
}

void neuralnetwork::save() {
    // check if the path has been saved
    if (! std::filesystem::is_regular_file(this->path_to_file) ) {
        std::cerr << "Can not open file\n";
        exit(1);
    }
    this->save(this->path_to_file);
}

bool neuralnetwork::operator==(neuralnetwork b) {
    // compare the two networks
    //return (this->sizes == b.sizes && this->weights == b.weights && this->biases == b.biases);

    if (this->sizes != b.sizes) { return false; }

    for (int i = 0; i < this->weights.size(); i++) {
        if (this->weights[i] != b.weights[i]) { return false; }
    }

    for (int i = 0; i < this->biases.size(); i++) {
        if (this->biases[i] != b.biases[i]) { return false; }
    }

    return true;
}

};