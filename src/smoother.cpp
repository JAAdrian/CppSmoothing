#include "smoother.hpp"

/* ============================================================================
        Recursive Averaging
============================================================================ */

RecursiveAveraging::RecursiveAveraging(double time_constant, int sample_rate) {
    this->alpha = 1 - exp(-1 / (time_constant * sample_rate));
}

void RecursiveAveraging::set_initial_value(double sample) {
    previous_value = sample;
}

double RecursiveAveraging::step(double sample) {
    double smoothed_sample = alpha*sample + (1-alpha)*previous_value;
    previous_value = smoothed_sample;
    return smoothed_sample;
}

void RecursiveAveraging::reset() {
    previous_value = 0;
}

/* ============================================================================
        Alpha Beta Filter
============================================================================ */

AlphaBetaFilter::AlphaBetaFilter(double alpha, double beta, int sample_rate) {
    this->alpha = alpha;
    this->beta = beta;

    sample_period = (double) 1 / sample_rate;
}

void AlphaBetaFilter::set_initial_value(double sample) {
    previous_position = sample;
}

void AlphaBetaFilter::set_initial_value(double position, double velocity) {
    previous_position = position;
    previous_velocity = velocity;
}

void AlphaBetaFilter::step(double sample, double *position_ptr, double *velocity_ptr) {
    double residual = 0;

    // propagate states
    double position = previous_position + (previous_velocity * sample_period);
    double velocity = previous_velocity;

    residual = sample - position;

    // update states
    position += alpha * residual;
    velocity += (beta * residual) / sample_period;

    previous_position = position;
    previous_velocity = velocity;

    position_ptr = &position;
    velocity_ptr = &velocity;
}

void AlphaBetaFilter::reset() {
    previous_position = 0;
    previous_velocity = 0;
}
