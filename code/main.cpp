#include "utils.h"
#include <vector>
#include <iostream>


int main(int argc, char *argv[]) {

    arma::mat V;
    std::cout << argc << std::endl;
    if (argc == 2){
            std::string filename = argv[1];
            V.load(arma::csv_name(filename));
    }
    else{
        V = arma::mat(3, 3, arma::fill::eye);
    }

    std::cout << V << std::endl;

    // int M = 5;
    // double h = 0.005;
    // double dt = 2.5e-5;

    // double xc = 0.25;
    // double x = 0;
    // double sigma_x = 0.05;
    // double px = 200;

    // double yc = 0.5;
    // double y = 0;
    // double sigma_y = 0.05;
    // double py = 0;

    // PDESolver test = PDESolver(M, h, dt);

    // test.make_mat();
    // arma::cx_mat U = test.create_u_mat(xc, yc, x, y, sigma_x, sigma_y, px, py);

    // test.normalized_U(U);

    // std::cout << std::endl;
    // std::cout << U << std::endl;

    // std::cout << test.A << std::endl;
    // std::cout << test.B << std::endl;

    return 0;
}
