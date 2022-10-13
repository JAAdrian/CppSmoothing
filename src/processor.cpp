#include <memory>

#include "processor.h"
#include "smoother.hpp"

std::unique_ptr<AlphaBetaFilter> processor;

extern void initialize(double alpha, double beta, int sample_rate) {
    processor = std::make_unique<AlphaBetaFilter>(alpha, beta, sample_rate);
    processor->set_initial_value(0.0, 0.0);
}

extern void step(double sample, double *position, double *velocity) {
    processor->step(sample, position, velocity);
}

extern void reset() {
    processor->reset();
}

extern void terminate() {
    processor.reset();
}


