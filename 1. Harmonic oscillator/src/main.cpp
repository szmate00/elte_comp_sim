/////////////////////////////////////////////////////////////////////
// Simple harmonic oscillator using Euler and Euler-Cromer methods //
// @Máté Szűcs, 2022                                               //
/////////////////////////////////////////////////////////////////////

#include <cmath>

#include "utils.hpp"


int main(int argc, char const *argv[]) {
    if(argc != 7) {
        std::cout << "ERROR!\n" << "------" << std::endl;
        std::cout << "NOT ENOUGH ARGUMENTS WERE GIVEN!" << std::endl;
        std::cout << "Usage: ./main <x0> <v0> <omega> <periods> <stepsPerPeriod> <outFile>" << std::endl;
        std::cout << "Exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }

    const double pi = 4 * atan(10);
    
    double x0 = std::stod(argv[1]);
    double v0 = std::stod(argv[2]);
    double omega = std::stod(argv[3]);
    double periods = std::stod(argv[4]);
    double stepsPerPeriod = std::stod(argv[5]);
    std::string outFile = argv[6];

    std::string path = "../out/";
    std::string outE = path + outFile + "E.txt";
    std::string outEC = path + outFile + "EC.txt";
    std::string outERun = path + outFile + "ERun.txt";
    std::string outECRun = path + outFile + "ECRun.txt";

    double T = 2 * pi / omega;
    double dt = T / stepsPerPeriod;
    int sumSteps = stepsPerPeriod * periods;

    // Euler method
    Euler(x0, v0, omega, dt, sumSteps, outE);
    std::cout << "Euler method done!\n\n";

    // Euler-Cromer method
    EulerCromer(x0, v0, omega, dt, sumSteps, outEC);
    std::cout << "Euler-Cromer method done!\n\n";

    // Step number - runtime
    EulerRuntime(x0, v0, omega, dt, outERun);
    EulerCromerRuntime(x0, v0, omega, dt, outECRun);
    std::cout << "Runtime analysis done!\n\n\n";

    std::cout << "All finished!\nResults saved to: " << path;


    return 0;    
}