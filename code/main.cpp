#include "utils.h"
#include <vector>
#include <iostream>
#include<iomanip>



int main(int argc, char *argv[]) {
    
    double h = 0.005; 
    int M = 1./h+1.; //using h to get M. n_steps = M-1 and n_steps*h = 1...
    //std::cout << M << std::endl;
    //int M = 7;
    double dt = 2.5e-5;

    double xc = 0.25;
    double x = 0;
    double sigma_x = 0.05;
    double px = 200;

    double yc = 0.5;
    double y = 0;
    double sigma_y = 0.05;
    double py = 0;

    //define V here I guess

    
    //problem 5 with specified V
    arma::mat V = arma::zeros(M-2,M-2);
    int middle_index = (M-2-1)/2;

    int x_s = 0.02/h;
    int x_p = 0.02/h +1; //x_p = 5
    double V_0 = 100;
    
    //filling V 
    for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
        for (int y = 0; y< M-2;y++){
            V(y,i) = V_0;
        }
    }
    int y_s = 0.05/h;
    for (int y = middle_index+y_s/2.;y<=middle_index+2*y_s/2;y++){
        for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
            V(y,i) = 0;
        }
    }
    for (int y = middle_index-2*y_s/2.;y<=middle_index-y_s/2;y++){
        for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
            V(y,i) = 0;
        }
    } 
    std::ofstream ofile;
    //std::string filename = "L_" + std::to_string(N) + "_T_"  + std::to_string(temp) + "_" + rand + ".txt";
    ofile.open("lol.txt");
    ofile << V << std::endl;
    ofile.close(); 

    PDESolver test = PDESolver(M, h, dt,V);

    test.make_mat();
    //std::cout << test.A << std::endl;
    ///arma::cx_mat U = test.create_u_mat(xc, yc, x, y, sigma_x, sigma_y, px, py);

    ///test.normalized_U(U);

    ///std::cout << std::endl;
    ///std::cout << U << std::endl;

    // std::cout << test.A << std::endl;
    // std::cout << test.B << std::endl;

    return 0;
}
