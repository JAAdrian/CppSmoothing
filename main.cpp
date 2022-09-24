#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "processor.hpp"

using namespace std;

const int SAMPLE_RATE = 1000;
const int NUM_SECONDS = 3;
const int BOUNDARY_ONE_SEC = 1;
const int BOUNDARY_TWO_SEC = 2;

int main() {
    int num_total_samples = round(SAMPLE_RATE * NUM_SECONDS);
    int boundary_one_samples = round(SAMPLE_RATE * BOUNDARY_ONE_SEC);
    int boundary_two_samples = round(SAMPLE_RATE * BOUNDARY_TWO_SEC);

    double time_constant = (double) NUM_SECONDS / 50;

    RecursiveAveraging processor(time_constant, SAMPLE_RATE);

    random_device rd{};
    mt19937 gen{rd()};

    normal_distribution<double> first{0, 1};
    normal_distribution<double> second{5, 2};
    normal_distribution<double> third{-3, 0.5};

    ofstream csv_file("output.csv");
    csv_file << "noise_sample, smoothed_sample" << "\n";

    double smoothed_sample;
    double sample;
    vector<double> original_sample;
    vector<double> smoothed_samples;
    for (int sample_index = 0; sample_index < num_total_samples; sample_index++) {
        if (sample_index < boundary_one_samples) {
            sample = first(gen);
        } else if (
            (sample_index >= boundary_one_samples) &&
            (sample_index < boundary_two_samples)
        ) {
            sample = second(gen);
        } else {
            sample = third(gen);
        }

        smoothed_sample = processor.step(sample);

        original_sample.push_back(sample);
        smoothed_samples.push_back(smoothed_sample);

        // cout << sample << "\t" << smoothed_sample << endl;
        csv_file << sample << ", " << smoothed_sample << "\n";
    }

    csv_file << "\n";
    csv_file.close();
    return 0;
}
