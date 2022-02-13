/////////////////////////////////////////////////////////////////////
// Checking the relationship between step number and runtime.      //
// @Máté Szűcs, 2022                                               //
/////////////////////////////////////////////////////////////////////

#include <chrono>

#include "utils.hpp"


int main(int argc, char const *argv[]) {
    if(argc != 5) {
        std::cout << "ERROR!\n" << "------" << std::endl;
        std::cout << "NOT ENOUGH ARGUMENTS WERE GIVEN!" << std::endl;
        std::cout << "Usage: ./main <x0> <v0> <omega> <periods> <stepsPerPeriod> <outFile>" << std::endl;
        std::cout << "Exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }

    double dt;
    int sumSteps;
    const double pi = 4 * atan(10);
    
    double x0 = std::stod(argv[1]);
    double v0 = std::stod(argv[2]);
    double omega = std::stod(argv[3]);
    double periods = std::stod(argv[4]);

    std::string path = "../out/";
    std::string outE = path + outFile + "E.txt";
    std::string outEC = path + outFile + "EC.txt";

    std::vector stepsPerPeriod = {10, 25, 50, 100, 150, 200, 500, 750, 1000};

    double T = 2 * pi / omega;

    for (auto stepNum: stepsPerPeriod) {
        dt = T / stepNum;
        sumSteps = stepNum * periods;

        auto t1E = std::chrono::high_resolution_clock::now();
    
        Euler(x0, v0, omega, dt, sumSteps, outE);

        auto t2E = std::chrono::high_resolution_clock::now();
        double tSumE = double((static_cast<std::chrono::duration<double, std::milli>>(t2E-t1E)).count());
        std::cout << "Euler method done!\nEllapsed time: " << tSumE << " ms.\n\n";


        auto t1EC = std::chrono::high_resolution_clock::now();
        
        EulerCromer(x0, v0, omega, dt, sumSteps, outEC);

        auto t2EC = std::chrono::high_resolution_clock::now();
        double tSumEC = double((static_cast<std::chrono::duration<double, std::milli>>(t2EC-t1EC)).count());
        std::cout << "Euler-Cromer method done!\nEllapsed time: " << tSumEC << " ms.\n\n\n";

        std::cout << "All finished!\nResults saved to: " << path;