////////////////////////////////////////////
// Auxiliary functions for the assignment //
// @Máté Szűcs, 2022                      //
////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <chrono>
#include <vector>


double energy(double x, double v, double omega) {
    return 0.5 * (v * v + omega * omega * x * x);
}

void Euler(double x0, double v0, double omega, double dt, int steps, std::string outFile) {
    double a, v_temp;
    double x = x0;
    double v = v0;
    double t = 0.0;

    std::ofstream ofile(outFile);
    if (!ofile) {
        std::cerr << "Cannot open file!";
        exit(EXIT_FAILURE);
    }

    ofile << t << "\t" << x << "\t" << v << "\t" << energy(x, v, omega) << std::endl;

    for (int i = 0; i < steps; i++) {
        a = -omega * omega * x;
        v_temp = v;
        v += a * dt;
        x += v_temp * dt;
        t += dt;

        ofile << t << "\t" << x << "\t" << v << "\t" << energy(x, v, omega) << std::endl;
    }
    ofile.close();
}

void EulerCromer(double x0, double v0, double omega, double dt, int steps, std::string outFile) {
    double a;
    double x = x0;
    double v = v0;
    double t = 0.0;

    std::ofstream ofile(outFile);
    if (!ofile) {
        std::cerr << "Cannot open file!";
        exit(EXIT_FAILURE);
    }

    ofile << t << "\t" << x << "\t" << v << "\t" << energy(x, v, omega) << std::endl;

    for (int i = 0; i < steps; i++) {
        a = -omega * omega * x;
        v += a * dt;
        x += v * dt;
        t += dt;

        ofile << t << "\t" << x << "\t" << v << "\t" << energy(x, v, omega) << std::endl;
    }
    ofile.close();
}

void EulerRuntime(double x0, double v0, double omega, double dt, std::string outFile) {
    double a, v_temp;
    double x = x0;
    double v = v0;

    std::vector<int> stepsVec = {75000, 100000, 150000, 200000, 250000, 300000, 500000, 750000, 1000000};

    std::ofstream ofile(outFile);
    if (!ofile) {
        std::cerr << "Cannot open file!";
        exit(EXIT_FAILURE);
    }

    for (auto steps: stepsVec) {
        auto t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < steps; i++) {
            a = -omega * omega * x;
            v_temp = v;
            v += a * dt;
            x += v_temp * dt;
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        double tSum = double((static_cast<std::chrono::duration<double, std::milli>>(t2 - t1)).count());

        ofile << steps << "\t" << tSum << std::endl;
    }

    ofile.close();
}

void EulerCromerRuntime(double x0, double v0, double omega, double dt, std::string outFile) {
    double a;
    double x = x0;
    double v = v0;

    std::vector<int> stepsVec = {75000, 100000, 150000, 200000, 250000, 300000, 500000, 750000, 1000000};

    std::ofstream ofile(outFile);
    if (!ofile) {
        std::cerr << "Cannot open file!";
        exit(EXIT_FAILURE);
    }

    for (int steps: stepsVec) {
        auto t1 = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < steps; i++) {
            a = -omega * omega * x;
            v += a * dt;
            x += v * dt;
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        double tSum = double((static_cast<std::chrono::duration<double, std::milli>>(t2 - t1)).count());

        ofile << steps << "\t" << tSum << std::endl;
    }

    ofile.close();
}