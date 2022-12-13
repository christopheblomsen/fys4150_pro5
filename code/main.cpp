// Build
// g++ -I include src/* main.cpp -o main -larmadillo -O2
//
// Run
// ./main input_parameters.csv
#include "utils.h"
#include "PDESolver.h"
#include "box.h"


int main(int argc, char** argv){
    // Define all parameters
    arma::mat V, input;
    int slit, M;
    double h, dt, T, x, xc, sigma_x, px, y, yc, sigma_y, py, v0;
    std::string potential, filename, savefile;

    // make sure that input csv file is given
    if (argc == 2){
        // for reading and saving the data
        filename = argv[1];
        savefile = get_name(filename);

        input.load(arma::csv_name(filename));
        input.shed_row(0);

        // initialization of variables
        h = input(0);
        dt = input(1);
        T = input(2);

        xc = input(3);
        sigma_x = input(4);
        px = input(5);

        yc = input(6);
        sigma_y = input(7);
        py = input(8);

        v0 = input(9);
        slit = input(10);

        M = (int)(1./h) + 1; //using h to get M. n_steps = M-1 and n_steps*h = 1...
    }
    else{
        std::cout << "Need to run with input parameters" << std::endl;
        std::cout << "argv[1] is the filename of the input parameters" << std::endl;
        return 1;
    }
    // Sets up the box with wall
    Box box(M, h, dt, filename, slit, v0);
    V = box.potential_well();

    PDESolver PDE = PDESolver(M, h, dt, V);
    std::cout << "Starting simulation" << std::endl;
    arma::cx_mat U = PDE.simulation(xc, yc, sigma_x, sigma_y, px, py, T);
    std::cout << "Simulation done" << std::endl;
    U.save(savefile);

    return 0;
}
