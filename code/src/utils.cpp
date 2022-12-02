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
