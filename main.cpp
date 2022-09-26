#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
#include "processor.hpp"

using namespace std;

const int SAMPLE_RATE = 1000;
const int NUM_SECONDS = 3;
const int BOUNDARY_ONE_SEC = 1;
const int BOUNDARY_TWO_SEC = 2;

void execute_recursive_averaging(
    int num_total_samples,
    int boundary_one_samples,
    int boundary_two_samples,
    double alpha
) {
    random_device rd{};
    mt19937 gen{rd()};

    normal_distribution<double> first{0, 1};
    normal_distribution<double> second{5, 2};
    normal_distribution<double> third{-3, 0.5};

    double time_constant = (double) -1 / log(1 - alpha) / SAMPLE_RATE;
    RecursiveAveraging processor(time_constant, SAMPLE_RATE);
    processor.set_initial_value(0);

    ofstream csv_file("data/output.csv");
    csv_file << "noise_sample,smoothed_sample" << "\n";

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

        csv_file << sample << "," << smoothed_sample << "\n";
    }

    csv_file << "\n";
    csv_file.close();
}


void execute_alpha_beta_filter(
    int num_total_samples,
    int boundary_one_samples,
    int boundary_two_samples,
    double alpha,
    double beta
) {
    random_device rd{};
    mt19937 gen{rd()};

    normal_distribution<double> first{0, 1};
    normal_distribution<double> second{5, 2};
    normal_distribution<double> third{-3, 0.5};

    AlphaBetaFilter processor(alpha, beta, SAMPLE_RATE);
    processor.set_initial_value(0, 0);

    ofstream csv_file("data/output_alpha_beta_filter.csv");
    csv_file << "noise_sample,smoothed_sample,velocity" << "\n";

    double smoothed_sample = 0;
    double velocity_estimate = 0;
    double sample = 0;
    vector<double> original_sample;
    vector<double> smoothed_samples;
    vector<double> velocities;
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

        processor.step(sample, smoothed_sample, velocity_estimate);

        original_sample.push_back(sample);
        smoothed_samples.push_back(smoothed_sample);
        velocities.push_back(velocity_estimate);

        csv_file << sample << "," << smoothed_sample << "," << velocity_estimate << "\n";
    }

    csv_file << "\n";
    csv_file.close();
}


int main(int argc, char* argv[]) {
    int num_total_samples = round(SAMPLE_RATE * NUM_SECONDS);
    int boundary_one_samples = round(SAMPLE_RATE * BOUNDARY_ONE_SEC);
    int boundary_two_samples = round(SAMPLE_RATE * BOUNDARY_TWO_SEC);

    double alpha_1 = stod(argv[1]);
    double alpha_2 = stod(argv[2]);
    double beta = stod(argv[3]);

    execute_recursive_averaging(
        num_total_samples,
        boundary_one_samples,
        boundary_two_samples,
        alpha_1
    );
    execute_alpha_beta_filter(
        num_total_samples,
        boundary_one_samples,
        boundary_two_samples,
        alpha_2,
        beta
    );

    return 0;
}
