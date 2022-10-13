#pragma once

#include <cmath>

class RecursiveAveraging {
    public:
        RecursiveAveraging(double time_constant, int sample_rate);
        void set_initial_value(double sample);
        double step(double sample);
        void reset();

    private:
        double previous_value = 0;
        double alpha;
};

class AlphaBetaFilter {
    public:
        AlphaBetaFilter(
            double alpha,
            double beta,
            int sample_rate
        );
        void set_initial_value(double sample);
        void set_initial_value(double sample, double velocity);
        void step(
            double sample,
            double *position,
            double *velocity
        );
        void reset();

    private:
        double sample_period;
        double previous_position;
        double previous_velocity;
        double alpha;
        double beta;
};
