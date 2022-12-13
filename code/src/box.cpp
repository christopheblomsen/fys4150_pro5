#include "box.h"
#include "utils.h"

// Constructor
Box::Box(int M_input, double h_input, double dt_input,
         std::string filename_in, int slit_input, double V_0_input){
    M = M_input;
    h = h_input;
    dt = dt_input;
    filename = filename_in;
    slit = slit_input;
    V_0 = V_0_input;
}

// Loads the potential well into a matrix
arma::mat Box::potential_well(){
    arma::mat V;
    std::string potential = potential_file(slit);
    if (!exists(potential)){
        making_potential(potential);
    }
    V.load(arma::csv_name(potential));
    return V;
}

// If the file doesn't exists, will make a csv file
void Box::making_potential(std::string potential){
    std::cout << potential << " did not exist and will be created" << std::endl;
    make_file(potential);
}

// Actually makes the file without the message
void Box::make_file(std::string potential){
    switch (slit){
        case 0:
            write2file(potential, no_slit());
            break;
        case 1:
            write2file(potential, single_slit());
            break;
        case 2:
            write2file(potential, double_slit());
            break;
        case 3:
            write2file(potential, triple_slit());
            break;
        default:
            std::cout << "Slit param not understood" << std::endl;
    }
}

// The potential well with no slit
arma::mat Box::no_slit(){
    arma::mat V = arma::zeros(M-2, M-2);
    int middle_index = (M-2-1)/2;

    int x_s = int(0.02/h);
    int x_p = int(0.02/h +1);
    int y_s = 0.05/h;

    //filling V
    //filling x
    for (int i = 0; i <= (M-3); i++){
            V(M-3,i) = V_0;
            V(0,i) = V_0;
    }

    return V;
}
 
// The potential well with one slit
arma::mat Box::single_slit(){
    arma::mat V = arma::zeros(M-2, M-2);
    int middle_index = (M-2-1)/2;

    int x_s = int(0.02/h);
    int x_p = int(0.02/h +1);
    int y_s = 0.05/h;

    //filling V
    //filling x
    for (int i = middle_index - x_s/2.; i <= middle_index + x_s/2; i++){
        for (int y = 0; y < M-2; y++){
            V(i,y) = V_0;
        }
    }

    //creating first slip
    for (int y = middle_index - y_s/2.; y <= middle_index + y_s/2; y++){
        for (int i = middle_index - x_s/2.;i <= middle_index + x_s/2; i++){
            V(i,y) = 0;
        }
    }

    return V;
}

// The potential well with two slits
arma::mat Box::double_slit(){
    arma::mat V = arma::zeros(M-2, M-2);
    int middle_index = (M-2-1)/2;

    int x_s = int(0.02/h);
    int x_p = int(0.02/h + 1);

    //filling V
    //filling x
    for (int i = middle_index - x_s/2.; i <= middle_index + x_s/2; i++){
        for (int y = 0; y < M-2; y++){
            V(i,y) = V_0;
        }
    }

    //creating first slip
    int y_s = 0.05/h;
    for (int y = middle_index + y_s/2.; y <= middle_index + 2*y_s/2; y++){
        for (int i = middle_index - x_s/2.; i <= middle_index + x_s/2; i++){
            V(i,y) = 0;
        }
    }
    //creating second slit
    for (int y = middle_index - 2*y_s/2.; y <= middle_index - y_s/2; y++){
        for (int i = middle_index - x_s/2.; i <= middle_index + x_s/2; i++){
            V(i,y) = 0;
        }
    }
    return V;
}

// The potential well with three slits
arma::mat Box::triple_slit(){
    arma::mat V = arma::zeros(M-2, M-2);
    int middle_index = (M-2-1)/2;

    int x_s = int(0.02/h);
    int x_p = int(0.02/h + 1);
    int y_s = 0.05/h;

    //filling V
    //filling x
    for (int i = middle_index - x_s/2.;i <= middle_index + x_s/2; i++){
        for (int y = 0; y < M-2; y++){
            V(i,y) = V_0;
        }
    }

    //creating first slip
    for (int y = middle_index - y_s/2; y <= middle_index + y_s/2; y++){
        for (int i = middle_index - x_s/2; i <= middle_index + x_s/2; i++){
            V(i,y) = 0;
        }
    }
    
    //creating second slit
    for (int y = middle_index + y_s/2 + y_s; y <= middle_index + y_s/2 + y_s + y_s; y++){
        for (int i = middle_index - x_s/2; i <= middle_index + x_s/2; i++){
            V(i,y) = 0;
        }
    }


     //creating third slit
    for (int y = middle_index - y_s/2 - y_s - y_s; y <= middle_index - y_s/2 - y_s; y++){
        for (int i = middle_index - x_s/2.; i <= middle_index + x_s/2; i++){
            V(i,y) = 0;
        }
    }
    return V;
}

// Writes the potential to csv file
void Box::write2file(std::string filename, arma::mat V){
    V.save(arma::csv_name(filename));
}
