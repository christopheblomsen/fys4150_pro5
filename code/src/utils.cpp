#include "utils.h"
#include <armadillo>

// takes an index pair (i,j) and gets the
// single index k in the vector
int index2k(int i, int j){
    return i + j*(M-2);
}

void make_diag(int M, double h, double dt, arma::cx_mat){
    for (int i = 0; i <= (M-2); i++){

    }
}

// this function solves the linear matrix equation to find the n+1 step
arma::vec one_step(arma::mat A, arma::mat B, arma::vec u_n){
    
    // First step 
    arma::vec b = B * u_n;
    
    // Now we solve the system with arma::solve, can implement own function later
    arma::vec u_n1;
    u_n1 = arma::solve(A, b);

    return u_n1;
}