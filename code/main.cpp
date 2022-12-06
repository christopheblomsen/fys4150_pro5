#include "utils.h"
#include <vector>
#include <iostream>


int main(int argc, char *argv[]) {

    int M = 5;
    double h = 0.005;
    double dt = 2.5e-5;

    double xc = 0.25;
    double x = 0;
    double sigma_x = 0.05;
    double px = 200;

    double yc = 0.5;
    double y = 0;
    double sigma_y = 0.05;
    double py = 0;

    //define V here I guess

    arma::mat V = arma::zeros(M-2,M-2);
    V(0,2) = 5;
    std::cout << V << std::endl;
    
    PDESolver test = PDESolver(M, h, dt,V);

    test.make_mat();
    //std::cout << test.A << std::endl;
    ///arma::cx_mat U = test.create_u_mat(xc, yc, x, y, sigma_x, sigma_y, px, py);

    ///test.normalized_U(U);

    ///std::cout << std::endl;
    ///std::cout << U << std::endl;

    // std::cout << test.A << std::endl;
    // std::cout << test.B << std::endl;

    return 0;
}
