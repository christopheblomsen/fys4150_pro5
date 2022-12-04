#include "utils.h"
#include <vector>
#include <iostream>


int main(int argc, char *argv[]) {

    int M = 5;
    double h = 0.005;
    double dt = 2.5e-5;

    PDESolver test = PDESolver(M, h, dt);

    test.make_mat();

    // std::cout << test.A << std::endl;
    // std::cout << test.B << std::endl;

    return 0;
}
