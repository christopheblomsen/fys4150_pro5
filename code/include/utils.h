#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <armadillo>

// takes an index pair (i,j) and gets the
// single index k in the vector
int index2k(int i, int j, int M);

void make_vec(arma::cx_vec &a, arma::cx_vec &b, int M,
              double h, double dt, arma::mat V, arma::cx_double r);

void make_mat(arma::cx_vec &a, arma::cx_vec &b, arma::cx_double r,
              int M, arma::sp_cx_mat &A, arma::sp_cx_mat &B);

/* arma::cx_double a_coeff(int k, arma::cx_double r, arma::cx_double v); */
/* arma::cx_double b_coeff(int k, arma::cx_double r); */

/* std::vector<arma::cx_mat> make_mat(int M, double h, double dt, arma::cx_mat V); */
void make_diag(int M, double h, double dt, arma::cx_mat V);

arma::vec one_step(arma::mat A, arma::mat B, arma::vec u_n);

#endif // UTILS_H_
