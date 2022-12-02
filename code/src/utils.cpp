#include "utils.h"
#include <armadillo>

using namespace std::complex_literals;

// takes an index pair (i,j) and gets the
// single index k in the vector
int index2k(int i, int j, int M){
    return i + j*(M-2);
}

void make_vec(arma::cx_vec &a, arma::cx_vec &b, int M,
              double h, double dt, arma::mat V, arma::cx_double r){
    arma::cx_double coeff = arma::cx_double(0, dt/2.);
    for (int j = 0; j < V.n_rows; j++){
        for (int i = 0; i < V.n_rows; i++){
            a(i*V.n_cols + j) = 1. + 4.*r + coeff*V(i,j);
            b(i*V.n_cols + j) = 1. - 4.*r - coeff*V(i,j);
        }
    }
}

void make_mat(arma::cx_vec &a, arma::cx_vec &b, arma::cx_double r,
              int M, arma::sp_cx_mat &A, arma::sp_cx_mat &B){
    int N = M-2;
    for (int i = 0; i <= M-3; i++){
        for (int j = 0; j < M-2; j++){
            // int k = index2k(i, j, M);
            std::cout << "i: " << i << std::endl;
            std::cout << "j: " << j << std::endl;
            // std::cout << "k: " << k << std::endl;
            A(i, i) = a(i, j);
            B(i, i) = b(i, j);
        }
    }

}

// arma::cx_double a_coeff(int k, arma::cx_double r, double dt, arma::cx_double v){
//     arma::cx_double a;
//     a = 1. + 4.*r + 1i*dt/2. * v;
//     return a;
// }

// arma::cx_double b_coeff(int k, arma::cx_double r, double dt){
//     arma::cx_double b;
//     b = 1. - 4.*r - 1i*dt/2. * v;
//     return b;
// }

// std::vector<arma::cx_mat> make_mat(int M, double h, double dt, arma::cx_mat V){
//     // int N = (M-2);
//     std::cout << V << std::endl;
//     int N = 3;
//     arma::cx_mat A = arma::cx_mat(N, N, arma::fill::eye);
//     arma::cx_mat B = arma::cx_mat(N, N, arma::fill::eye);
//     // std::cout << A << std::endl;
//     arma::cx_double r = 1i*dt/(2.*h*h);
//     for (int i = 0; i <= N; i++){
//         for (int j = 0; j < N; j++){
//             std::cout << "j: " << j << std::endl;
//             arma::cx_vec v(arma::ones);
//             int k = index2k(i, j, M);
//             std::cout << k <<std::endl;
//             arma::cx_double a = a_coeff(k, r, dt, v(k));
//             std::cout << a << std::endl;
//             // A(i, i) = a_coeff(k, r, dt);
//             // std::cout << A(k, k) << std::endl;
//             // B(i, i) = b_coeff(k, r, dt);
//         }
//         for (int j = 0; j < N; j++){
//             int k = index2k(i, j, M);
//             int k1 = index2k(i+1, j, M);
//             int k2 = index2k(i, j+1, M);

//             A(k1, k) = -r;
//             A(k, k2) = -r;

//             B(k1, k) = r;
//             B(k, k2) = r;
//         }
//     }
//     std::vector<arma::cx_mat> data{A, B};
//     return data;
// }
// this function solves the linear matrix equation to find the n+1 step
arma::vec one_step(arma::mat A, arma::mat B, arma::vec u_n){
    
    // First step 
    arma::vec b = B * u_n;
    
    // Now we solve the system with arma::solve, can implement own function later
    arma::vec u_n1;
    u_n1 = arma::solve(A, b);

    return u_n1;
}
