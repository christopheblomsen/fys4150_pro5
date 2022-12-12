#ifndef BOX_H_
#define BOX_H_

#include <armadillo>
#include <iostream>

// Class that makes the csv files that describes the
// box the particle will be located in.
// Easy to visualize the csv files and see the shape
struct Box{
    Box(int M_input, double h_input, double dt_input,
        std::string filename_in, int slit_input);
    int M;
    double h;
    double dt;
    std::string filename;
    int slit;

    // Loads or
    arma::mat potential_well();
    void making_potential(std::string potential);

    // Makes the csv file, and corresponding sub methods
    void make_file();
    arma::mat no_slit();
    arma::mat single_slit();
    arma::mat double_slit();
    arma::mat triple_slit();

    void write2file(std::string filename, arma::mat V);
};


#endif // BOX_H_
