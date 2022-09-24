#pragma once

#include <cmath>

using namespace std;

class RecursiveAveraging {
    public:
        RecursiveAveraging(double time_constant, int sample_rate);
        double step(double sample);
        void reset();

    private:
        double previous_value;
        double alpha;
};
