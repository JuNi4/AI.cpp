/**
 * @file standardNormalDeviation.hpp
 * @author JuNi4
 * @brief Generate standard normal deviation numbers
 * @date 2023-04-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <random>
#include <chrono>

#ifndef _CMATH_SND_HPP_
#define _CMATH_SND_HPP_

namespace cmath {

// get current milleseconds function by
//  - Alessandro Pezzato
//  on <https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets>
uint64_t timeSinceEpochNanosec() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
}

/**
 * @brief Generate a random number based on standard normal deviation
 * 
 * @return double The random number
 */
double standardNormalDeviation() {
    std::default_random_engine generator((long int)timeSinceEpochNanosec());
    std::normal_distribution<double> distribution(0,2.0);

    double number = distribution(generator);

    return number;
}

};

#endif