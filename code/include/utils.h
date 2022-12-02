#ifndef UTILS_H_
#define UTILS_H_

#include <armadillo>
// takes an index pair (i,j) and gets the
// single index k in the vector
int index2k(int i, int j);

void make_diag(int M, double h, double dt, arma::cx_mat V);

arma::vec one_step(arma::mat A, arma::mat B, arma::vec u_n);

#endif // UTILS_H_
