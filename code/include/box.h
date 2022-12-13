#ifndef BOX_H_
#define BOX_H_

#include <armadillo>
#include <iostream>

// Class that makes the csv files that describes the
// box the particle will be located in.
// Easy to visualize the csv files and see the shape
struct Box{
    // Constructor
    Box(int M_input, double h_input, double dt_input,
        std::string filename_in, int slit_input, double V_0_input);

    // public variables
    int M;
    double h;
    double dt;
    std::string filename;
    int slit;
    double V_0;

    // Loads the potential well into a matrix
    arma::mat potential_well();

    // If the file doesn't exists, will make a csv file
    void making_potential(std::string potential);

    // Actually makes the file without the message
    void make_file(std::string potential);

    // The potential well with no slit
    arma::mat no_slit();

    // The potential well with one slit
    arma::mat single_slit();

    // The potential well with two slits
    arma::mat double_slit();

    // The potential well with three slits
    arma::mat triple_slit();

    // Writes the potential to csv file
    void write2file(std::string filename, arma::mat V);
};


#endif // BOX_H_
