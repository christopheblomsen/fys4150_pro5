#include "utils.h"
#include <armadillo>

using namespace std::complex_literals;

PDESolver::PDESolver(int M_input, double h_input, double dt_input){
    M = M_input;
    N = M-2;
    L = N*N;
    h = h_input;
    dt = dt_input;

    A = arma::sp_cx_mat(L, L);
    B = arma::sp_cx_mat(L, L);
    // A = arma::cx_mat(L, L);
    // B = arma::cx_mat(L, L);
    V = arma::mat(L, L, arma::fill::eye);

    r = 1i*dt/(2.*h*h);
    term = 1i*dt/2.;

}

// takes an index pair (i,j) and gets the
// single index k in the vector
int PDESolver::index2k(int i, int j){
    return i + j*(M-2);
}

// Makes the a and b vectors that are the main diagonal in
// the A and B matrixes
void PDESolver::make_vec(arma::cx_vec &a, arma::cx_vec &b){
    arma::cx_double term = 1i*dt/2.;
    for (int i=0; i < N; i++){
        for (int j=0; j < N; j++){
            int k = index2k(i, j);
            a(k) = 1. + 4.*r + term*V(i,j);
            b(k) = 1. - 4.*r - term*V(i,j);
        }
    }
}

// Make the "triangular" part of the matrix at the edges
void PDESolver::make_tri(arma::cx_vec &a, arma::cx_vec &b){
    A(0, 0) = a(0);
    A(0, 1) = -r;
    A(L-1, L-2) = -r;
    A(L-1, L-1) = a(L-1);

    B(0, 0) = b(0);
    B(0, 1) = r;
    B(L-1, L-2) = r;
    B(L-1, L-1) = b(L-1);
}

// Fills the rest of the matrixes
void PDESolver::fill_mat(arma::cx_vec &a, arma::cx_vec &b){
    make_tri(a, b);
    for (int i=1; i < L-1; i++){
        A(i, i-1) = -r;
        A(i, i+1) = -r;

        B(i, i-1) = r;
        B(i, i+1) = r;
    }
    for (int i=0; i < L-N; i++){
        A(i, N+i) = -r;
        A(N+i, i) = -r;

        B(i, N+i) = r;
        B(N+i, i) = r;
    }
}

// Makes the matrixes as stated in the assignment text
// Uses methods
//
// make_vec(arma::vec &a, arma::vec &b);
// fill_mat(arma::vec &a, arma::vec &b);
void PDESolver::make_mat(){
    arma::cx_vec a(L, arma::fill::zeros);
    arma::cx_vec b(L, arma::fill::zeros);

    make_vec(a, b);
    for (int k=0; k < L; k++){
        A(k, k) = a(k);
        B(k, k) = b(k);

    }

    // Fill the rest of the matrixes
    fill_mat(a, b);
}

arma::cx_double PDESolver::create_u_coeff(double xc, double yc,
                                          double x, double y,
                                          double sigma_x, double sigma_y,
                                          double px, double py){
    double x_term = -(x - xc)*(x - xc)/(2.*sigma_x*sigma_x);
    double y_term = -(y - yc)*(y - yc)/(2.*sigma_y*sigma_y);
    arma::cx_double x_momentum = 1i*px*(x - xc);
    arma::cx_double y_momentum = 1i*py*(y - yc);

    arma::cx_double term1 = std::exp(x_term + y_term);

    arma::cx_double u = term1 + x_momentum + y_momentum;
    return u;
}

arma::cx_mat PDESolver::create_u_mat(double xc, double yx,
                                     double x, double y,
                                     double sigma_x, double sigma_y,
                                     double px, double py){

    arma::cx_mat U(L, L, arma::fill::zeros);
    for (int i=1; i < L-1; i++){
        for (int j=1; j < L-1; j++){
            U(i, j) = create_u_coeff(xc, yx,
                                     x, y,
                                     sigma_x, sigma_y,
                                     px, py);
        }
    }

    return U;
}

void PDESolver::normalized_U(arma::cx_mat &U){
    U /= std::sqrt(arma::accu(arma::conj(U)%U));
}

// this function solves the linear matrix equation to find the n+1 step
arma::cx_vec PDESolver::one_step(arma::cx_vec u_n){
    
    // // First step
    // arma::cx_vec b = B * u_n;

    // // Now we solve the system with arma::solve, can implement own function later
    // arma::cx_vec u_n1;
    // u_n1 = arma::solve(A, b, arma::solve_opts::likely_sympd);

    arma::superlu_opts opts;
    opts.symmetric = true;

    arma::cx_vec u_n1;
    u_n1 = arma::zeros<arma::cx_vec>(u_n.n_elem);
    u_n1 = arma::spsolve(A, B*u_n, "superlu", opts);

    return u_n1;
}
