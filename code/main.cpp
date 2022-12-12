#include "utils.h"
#include "box.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

bool exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

void making_potential(std::string filename, int M,
                      double h, double dt, int slit){
    std::cout << filename << " did not exist and will be created" << std::endl;
    Box box(M, h, dt, filename, slit);
    box.make_file();
}

int main(int argc, char** argv) {
    arma::mat V;
    int slit, M;
    double h, dt, T, x, xc, sigma_x, px, y, yc, sigma_y, py, v0;
    std::string potential;

    if (argc == 2){
        std::string filename = argv[1];
        arma::mat input;
        input.load(arma::csv_name(filename));
        input.shed_row(0);

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

    switch (slit){
        case 0:
            potential = "no_slit.csv";
            if (!exists(potential)){
                making_potential(potential, M, h, dt, slit);
            }
            break;
        case 1:
            potential = "single_slit.csv";
            if (!exists(potential)){
                making_potential(potential, M, h, dt, slit);
            }
            break;
        case 2:
            potential = "double_slit.csv";
            if (!exists(potential)){
                making_potential(potential, M, h, dt, slit);
            }
            break;
        case 3:
            potential = "triple_slit.csv";
            if (!exists(potential)){
                making_potential(potential, M, h, dt, slit);
            }
            break;
        default:
            std::cout << "Potential file not understood" << std::endl;
            return 1;

    }
    V.load(arma::csv_name(potential));

    PDESolver test = PDESolver(M, h, dt,V);

    int n_steps = (int)(T/dt);
    // // int n_steps = 2;
    int L = test.L;
    std::cout << L << std::endl;

    test.make_mat();
    //std::cout << test.A << std::endl;
    arma::cx_mat U0 = test.create_u_mat(xc, yc, x, y, sigma_x, sigma_y, px, py);
    arma::cx_mat U(L, n_steps);
    std::cout << "mat done" << std::endl;
    // arma::cx_cube sim = test.simulation(U, 1);
    U.col(0) = test.extract_vec(U0);
    std::cout << "so far" << std::endl;
    for (int i=1; i < n_steps; i++){
        U.col(i) = test.one_step(U.col(i - 1));
    }
    std::cout << "simulation done?" << std::endl;
    U.save("test.bin");

    test.normalized_U(U);

    // std::cout << std::endl;
    // std::cout << sim << std::endl;

    std::cout << test.A << std::endl;
    std::cout << test.B << std::endl;

    return 0;
}
