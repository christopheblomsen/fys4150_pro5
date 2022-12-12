#ifndef BOX_H_
#define BOX_H_

#include <armadillo>
#include <iostream>

struct Box{
    Box(int M_input, double h_input, double dt_input,
        std::string filename_in, int slit_input);
    int M;
    double h;
    double dt;
    std::string filename;
    int slit;

    void make_file();
    arma::mat double_slit();
    arma::mat single_slit();
    arma::mat triple_slit();
    arma::mat no_slit();


    void write2file(std::string filename, arma::mat V);
};


#endif // BOX_H_
