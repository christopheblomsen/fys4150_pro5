#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <armadillo>

struct PDESolver{

    PDESolver(int M_input, double h_input, double dt_input,arma::mat V_input);

    int M;
    int N;
    int L;
    double h;
    double dt;
    

    // Use normal matrix to see the print and correct
    /* arma::cx_mat A; */
    /* arma::cx_mat B; */
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

    arma::cx_double create_u_coeff(double xc, double yc,
                                   double x, double y,
                                   double sigma_x, double sigma_y,
                                   double px, double py);

    arma::cx_mat create_u_mat(double xc, double yx,
                              double x, double y,
                              double sigma_x, double sigma_y,
                              double px, double py);

    void normalized_U(arma::cx_mat &U);

    arma::cx_cube simulation(arma::cx_mat U, double T);

    arma::cx_vec extract_vec(arma::cx_mat U);

    arma::cx_vec one_step(arma::cx_vec u_n);
};
#endif // UTILS_H_
