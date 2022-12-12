#include "utils.h"
#include "box.h"
#include <vector>
#include <iostream>
#include <iomanip>



int main(int argc, char *argv[]) {

    arma::mat V;
    double h = 0.005;
    int M = (int)(1./h) + 1; //using h to get M. n_steps = M-1 and n_steps*h = 1...
    // int M = 5;
    double dt = 2.5e-5;

    double T = 0.008;

    double x = 0;
    double xc = 0.25;
    double sigma_x = 0.05;
    double px = 200.;

    double y = 0;
    double yc = 0.5;
    double sigma_y = 0.05;
    double py = 0.;

    double v0 = 0;

    if (argc == 2){
            std::string filename = argv[1];
            V.load(arma::csv_name(filename));
    }
    else if (argc == 3){
        Box box(M, h, dt);
        V = box.double_slit();
        std::string filename = argv[1];
        box.write2file(filename, V);
    }
    else{
        std::cout << "Need to run with input parameters" << std::endl;
        std::cout << "argv[1] is the filename of the csv potential" << std::endl;
        std::cout << "argv[2] ís only if you want to remake the potential file" << std::endl;
        return 1;
    }

    PDESolver test = PDESolver(M, h, dt,V);

    // int n_steps = (int)(T/dt);
    int n_steps = 2;
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

    // test.normalized_U(U);

    // std::cout << std::endl;
    // std::cout << sim << std::endl;

    // std::cout << test.A << std::endl;
    // std::cout << test.B << std::endl;

    return 0;
}
