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

int main(int argc, char** argv) {
    arma::mat V;
    if (argc == 2){
        std::string filename = argv[1];
        arma::mat input;
        input.load(arma::csv_name(filename));
        input.shed_row(0);

        double h = input(0);
        double dt = input(1);
        double T = input(2);

        double x = input(3);
        double xc = input(4);
        double sigma_x = input(5);
        double px = input(6);

        double y = input(7);
        double yc = input(8);
        double sigma_y = input(9);
        double py = input(10);

        double v0 = input(11);
        int split = input(12);

        int M = (int)(1./h) + 1; //using h to get M. n_steps = M-1 and n_steps*h = 1...
    }
    else{
        std::cout << "Need to run with input parameters" << std::endl;
        std::cout << "argv[1] is the filename of the input parameters" << std::endl;
        return 1;
    }

    // std::string potential = "potential.csv";
    // if (exists(potential)){
    //         std::cout << "working" << std::endl;
    //     }
    switch (split){
        case 0:
            std::string potential = "no_slit.csv";
            if (exists(potential)){
                std::cout << "it exist" << std::endl;
            }
            break;
        case 1:
            std::string potential = "no_slit.csv";
            if (exists(potential)){
                std::cout << "it exist" << std::endl;
            }
            break;
        case 2:
            std::string potential = "no_slit.csv";
            if (exists(potential)){
                std::cout << "it exist" << std::endl;
            }
            break;
        case 3:
            std::string potential = "no_slit.csv";
            if (exists(potential)){
                std::cout << "it exist" << std::endl;
            }
            break;

    }

        // std::string filename = argv[1];
        // V.load(arma::csv_name(filename));
        // return 0;
    // else if (argc == 3){
    //     Box box(M, h, dt);
    //     V = box.filler_5();
    //     std::string filename = argv[1];
    //     box.write2file(filename, V);
    // }

    // PDESolver test = PDESolver(M, h, dt,V);

    // int n_steps = (int)(T/dt);
    // // int n_steps = 2;
    // int L = test.L;
    // std::cout << L << std::endl;

    // test.make_mat();
    // //std::cout << test.A << std::endl;
    // arma::cx_mat U0 = test.create_u_mat(xc, yc, x, y, sigma_x, sigma_y, px, py);
    // arma::cx_mat U(L, n_steps);
    // std::cout << "mat done" << std::endl;
    // // arma::cx_cube sim = test.simulation(U, 1);
    // U.col(0) = test.extract_vec(U0);
    // std::cout << "so far" << std::endl;
    // for (int i=1; i < n_steps; i++){
    //     U.col(i) = test.one_step(U.col(i - 1));
    // }
    // std::cout << "simulation done?" << std::endl;
    // U.save("test.bin");

    // test.normalized_U(U);

    // std::cout << std::endl;
    // std::cout << sim << std::endl;

    // std::cout << test.A << std::endl;
    // std::cout << test.B << std::endl;

    return 0;
}
