#include "box.h"
#include <armadillo>

Box::Box(int M_input, double h_input, double dt_input){
    M = M_input;
    h = h_input;
    dt = dt_input;

}

arma::mat Box::filler_5(){
    arma::mat V = arma::zeros(M-2, M-2);
    int middle_index = (M-2-1)/2;

    int x_s = int(0.02/h);
    int x_p = int(0.02/h +1); //x_p = 5
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
    return V;
}

void Box::write2file(std::string filename, arma::mat V){
    V.save(arma::csv_name(filename));
}
