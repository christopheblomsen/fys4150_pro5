#include "utils.h"
#include <armadillo>

using namespace std::complex_literals;

// takes an index pair (i,j) and gets the
// single index k in the vector
int index2k(int i, int j, int M){
    return i + j*M;
}

// This method will be used later in the make_mat
void make_vec(arma::cx_vec &a, arma::cx_vec &b, int M,
              double h, double dt, arma::mat V, arma::cx_double r){
    arma::cx_double coeff = arma::cx_double(0, dt/2.);
    std::cout << size(a) << std::endl;
    for (int j = 0; j < M-2; j++){
        std::cout << j << "test" << std::endl;
        for (int i = 0; i < M-2; i++){
            int k = index2k(i, j, M);
            std::cout << k << std::endl;
            // a(i*V.n_cols + j) = 1. + 4.*r + coeff*V(i,j);
            // b(i*V.n_cols + j) = 1. - 4.*r - coeff*V(i,j);
            a(k) = 1. + 4.*r + coeff*V(i,j);
            b(k) = 1. - 4.*r - coeff*V(i,j);
        }
    }
}

void make_mat(int M, double h, double dt, arma::mat V, arma::sp_cx_mat &A, arma::sp_cx_mat &B){
    //init
    int N = M-2;
    int L = N*N;
    int k = 0;
    arma::cx_double r = 1i*dt/(2.*h*h);
    arma::cx_double term = 1i*dt/2.;
    arma::cx_vec a(L, arma::fill::zeros);
    arma::cx_vec b(L, arma::fill::zeros);

    // make_vec(a, b, M, h, dt, V, r);
    // std::cout << N << std::endl;
    // std::cout << size(a) << std::endl;
    for (int i=0; i < N; i++){
        for (int j=0; j < N; j++){
            k = index2k(i, j, N);
            // std::cout << k << std::endl;
            a(k) = 1. + 4.*r + term*V(i,j);
            b(k) = 1. - 4.*r - term*V(i,j);
        }
    }

    std::cout << "so far so good" << std::endl;
    for (int i=0; i < L; i++){
        A(i, i) = a(i);
        B(i, i) = b(i);
    }


    // Setting up tri mat
    A(0, 0) = a(0);
    A(0, 1) = -r;
    A(L-1, L-2) = -r;
    A(L-1, L-1) = a(L-1);

    B(0, 0) = b(0);
    B(0, 1) = r;
    B(L-1, L-2) = r;
    B(L-1, L-1) = b(L-1);

    for (int i=1; i < L-1; i++){
        A(i, i-1) = -r;
        A(i, i+1) = -r;

        B(i, i-1) = r;
        B(i, i+1) = r;
    }

    // This is not neccesarry if we have filled with zeros, but for testing
    for (int i=N; i < L; i+=N){
        A(i, i-1) = 0.;
        A(i-1, i) = 0.;

        B(i, i-1) = 0.;
        B(i-1, i) = 0.;
    }
    for (int i=0; i < L-N; i++){
        A(i, N+i) = -r;
        A(N+i, i) = -r;

        B(i, N+i) = r;
        B(N+i, i) = r;
    }


}

// this function solves the linear matrix equation to find the n+1 step
arma::vec one_step(arma::mat A, arma::mat B, arma::vec u_n){
    
    // First step 
    arma::vec b = B * u_n;
    
    // Now we solve the system with arma::solve, can implement own function later
    arma::vec u_n1;
    u_n1 = arma::solve(A, b, arma::solve_opts::likely_sympd);

    return u_n1;
}
