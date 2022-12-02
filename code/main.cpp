#include "utils.h"
#include <vector>
#include <iostream>


int main(int argc, char *argv[]) {

    int M = 5;
    int N = M-2;
    double h = 0.005;
    double dt = 2.5e-5;
    arma::cx_double r = arma::cx_double(0, dt/(2.*h*h));

    arma::sp_cx_mat A = arma::sp_cx_mat(N, N);
    arma::sp_cx_mat B = arma::sp_cx_mat(N, N);
    arma::mat V = arma::mat(N, N, arma::fill::eye);

    arma::cx_vec a(9);
    arma::cx_vec b(9);

    make_vec(a, b, M, h, dt, V, r);
    make_mat(a, b, r, M, A, B);

    std::cout << b << std::endl;

    return 0;
}
