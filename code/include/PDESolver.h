#ifndef PDESOLVER_H_
#define PDESOLVER_H_

#include "utils.h"
#include <vector>
#include <armadillo>

struct PDESolver{

    // Constructor
    PDESolver(int M_input, double h_input, double dt_input,arma::mat V_input);

    int M;
    int N;
    int L;
    double h;
    double dt;
    

    arma::sp_cx_mat A;
    arma::sp_cx_mat B;
    arma::mat V;

    arma::cx_double r;
    arma::cx_double term;
    arma::cx_vec a;
    arma::cx_vec b;



    // takes an index pair (i,j) and gets the
    // single index k in the vector
    int index2k(int i, int j);

    // Makes the a and b vectors that are the main diagonal in
    // the A and B matrixes
    void make_vec(arma::cx_vec &a, arma::cx_vec &b);

    // Makes the matrixes as stated in the assignment text
    // Uses methods
    //
    // make_vec(arma::vec &a, arma::vec &b);
    // fill_mat(arma::vec &a, arma::vec &b);
    void make_mat();

    // Make the "triangular" part of the matrix at the edges
    void make_tri(arma::cx_vec &a, arma::cx_vec &b);

    // Fills the rest of the matrixes
    void fill_mat(arma::cx_vec &a, arma::cx_vec &b);

    // Creates the u coefficients in the U matrix
    arma::cx_double create_u_coeff(double xc, double yc,
                                   double x, double y,
                                   double sigma_x, double sigma_y,
                                   double px, double py);

    // Creates the U matrix
    arma::cx_mat create_u_mat(double xc, double yx,
                              double sigma_x, double sigma_y,
                              double px, double py);

    // Normalize the U matrix
    void normalized_U(arma::cx_mat &U);

    // Evolves the system from an initile state
    arma::cx_mat evolve(arma::cx_mat U0, double T);

    // Runs the simulation and saves as cube, not working
    arma::cx_cube simulation(arma::cx_mat U, double T);

    // Simulates the system and saves as a matrix
    // where each column is the corresponding timestep
    arma::cx_mat simulation(double xc, double yc,
                            double sigma_x, double sigma_y,
                            double px, double py, double T);

    // Extracts the column vector from U
    arma::cx_vec extract_vec(arma::cx_mat U);

    // this function solves the linear matrix equation to find the n+1 step
    arma::cx_vec one_step(arma::cx_vec u_n);
};
#endif // PDESOLVER_H_
