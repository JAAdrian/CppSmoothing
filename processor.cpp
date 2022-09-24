#include "processor.hpp"

using namespace std;

RecursiveAveraging::RecursiveAveraging(double time_constant, int sample_rate) {
    this->alpha = 1 - exp(-1 / (time_constant * sample_rate));
}

double RecursiveAveraging::step(double sample) {
    double smoothed_sample = alpha*sample + (1-alpha)*previous_value;
    previous_value = smoothed_sample;
    return smoothed_sample;
}

void RecursiveAveraging::reset() {
    previous_value = 0;
}
