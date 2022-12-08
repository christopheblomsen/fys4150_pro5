#ifndef BOX_H_
#define BOX_H_

#include <armadillo>
#include <iostream>

struct Box{
    Box(int M_input, double h_input, double dt_input);
    int M;
    double h;
    double dt;

    arma::mat filler_5();

    void write2file(std::string filename, arma::mat V);
};


#endif // BOX_H_
