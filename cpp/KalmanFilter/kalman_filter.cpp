#include <utility>
#include <vector>
#include <iostream>

// Use for an Altimeter or something
class KalmanFilter_1D {
public:
    // Constructor will initialize the Kalman Filter
    KalmanFilter_1D(double state, double variance) : x_hat(state), p(variance) {
        // Must follow initialization step with a prediction
        predict();
    }

    void predict() {
        // Calculate the predicted state for the next iteration using
        // system's Dynamic Model
        x_hat = x_hat;
        p = p;
    }

    // z_n = Measured system state
    // r_n = Measured variance
    void update(double z_n, double r_n) {
        // 1) Calculate the Kalman Gain
        double K_n = p / (p + r_n);
        // 2) Estimate the current state using the State Update Equation
        x_hat = x_hat + K_n * (z_n - x_hat);
        // 3) Update the current estimate uncertainty
        p = (1 - K_n) * p;
    }

    std::pair<double, double> get_outputs() {
        return std::pair<double,double>(x_hat, p);
    }

private:
    // Filter Inputs
    double x_hat; //Initial System State
    double p;     //Initial State Variance
};

class KalmanFilterTester {
public:
    KalmanFilterTester() : my_filter(60, 225) {
        // Let's print to screen what we are seeing
        std::pair<double,double> output = my_filter.get_outputs();
        std::cout << "Initial Guess\n";
        std::cout << "System state:\t" << output.first << "\n";
        std::cout << "State variance:\t" << output.second << "\n\n";
    }

    void run_test(const std::vector<double>& measurements, const std::vector<double>& variances) {
        for(int i = 0; i < measurements.size(); i++) {
            my_filter.update(measurements[i], variances[i]);
            std::pair<double,double> output = my_filter.get_outputs();

            // Let's print to screen what we are seeing
            std::cout << "Measurement #" << i+1 << ":\n";
            std::cout << "System state:\t" << output.first << "\n";
            std::cout << "State variance:\t" << output.second << "\n\n";

            my_filter.predict();
        }
    }

private:
    KalmanFilter_1D my_filter;
};



int main() {
    KalmanFilterTester tester;
    std::vector<double> measurements = {49.03, 48.44, 55.21, 49.98, 50.6, 52.61, 45.87, 42.64, 48.26, 55.84};
    std::vector<double> variances = {25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0};

    tester.run_test(measurements, variances);
    return 0;
}