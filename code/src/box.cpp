#include "box.h"
#include "utils.h"
#include <armadillo>

Box::Box(int M_input, double h_input, double dt_input,
         std::string filename_in, int slit_input){
    M = M_input;
    h = h_input;
    dt = dt_input;
    filename = filename_in;
    slit = slit_input;

}

arma::mat Box::potential_well(){
    arma::mat V;
    std::string potential = potential_file(slit);
    if (!exists(potential)){
        making_potential(potential);
    }
    V.load(arma::csv_name(potential));
    return V;
}

void Box::making_potential(std::string potential){
    std::cout << potential << " did not exist and will be created" << std::endl;
    Box box(M, h, dt, potential, slit);
    box.make_file();
}

void Box::make_file(){
    std::string filename;
    switch (slit){
        case 0:
            filename = "no_slit.csv";
            write2file(filename, no_slit());
            break;
        case 1:
            filename = "single_slit.csv";
            write2file(filename, single_slit());
            break;
        case 2:
            filename = "double_slit.csv";
            write2file(filename, double_slit());
            break;
        case 3:
            filename = "triple_slit.csv";
            write2file(filename, triple_slit());
            break;
        default:
            std::cout << "Slit param not understood" << std::endl;
    }
}


arma::mat Box::double_slit(){
    arma::mat V = arma::zeros(M-2, M-2);
    int middle_index = (M-2-1)/2;

    int x_s = int(0.02/h);
    int x_p = int(0.02/h +1); //x_p = 5
    double V_0 = 1e10;

    //filling V
    //filling x
    for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
        for (int y = 0; y< M-2;y++){
            V(i,y) = V_0;
        }
    }

    //creating first slip
    int y_s = 0.05/h;
    for (int y = middle_index+y_s/2.;y<=middle_index+2*y_s/2;y++){
        for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
            V(i,y) = 0;
        }
    }
    //creating second slit
    for (int y = middle_index-2*y_s/2.;y<=middle_index-y_s/2;y++){
        for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
            V(i,y) = 0;
        }
    }
    return V;
}


arma::mat Box::single_slit(){
    arma::mat V = arma::zeros(M-2, M-2);
    int middle_index = (M-2-1)/2;

    int x_s = int(0.02/h);
    int x_p = int(0.02/h +1); //x_p = 5
    int y_s = 0.05/h;

    double V_0 = 1e6;

    //filling V
    //filling x
    for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
        for (int y = 0; y< M-2;y++){
            V(i,y) = V_0;
        }
    }

    //creating first slip
    for (int y = middle_index-y_s/2.;y<=middle_index+y_s/2;y++){
        for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
            V(i,y) = 0;
        }
    }
    
    return V;
}


arma::mat Box::no_slit(){
    arma::mat V = arma::zeros(M-2, M-2);
    int middle_index = (M-2-1)/2;

    int x_s = int(0.02/h);
    int x_p = int(0.02/h +1); //x_p = 5
    int y_s = 0.05/h;

    double V_0 = 1e6;

    //filling V
    //filling x
    for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
        for (int y = 0; y< M-2;y++){
            V(i,y) = V_0;
        }
    }

    ////creating first slip
    //for (int y = middle_index-y_s/2.;y<=middle_index+y_s/2;y++){
    //    for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
    //        V(i,y) = 0;
    //    }
    //}
    
    return V;
}

arma::mat Box::triple_slit(){
    arma::mat V = arma::zeros(M-2, M-2);
    int middle_index = (M-2-1)/2;

    int x_s = int(0.02/h);
    int x_p = int(0.02/h +1); //x_p = 5
    int y_s = 0.05/h;
    double V_0 = 1e6;

    //filling V
    //filling x
    for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
        for (int y = 0; y< M-2;y++){
            V(i,y) = V_0;
        }
    }

    //creating first slip
    for (int y = middle_index-y_s/2;y<=middle_index+y_s/2;y++){
        for (int i = middle_index-x_s/2;i<=middle_index+x_s/2;i++){
            V(i,y) = 0;
        }
    }
    

    //for (int y = middle_index+y_s/2.;y<=middle_index+2*y_s/2;y++){
    //    for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
    //        V(i,y) = 0;
    //    }
    //}


    //creating second slit
    for (int y = middle_index+y_s/2+y_s;y <= middle_index + y_s/2+y_s+y_s;y++){
        for (int i = middle_index-x_s/2;i<=middle_index+x_s/2;i++){
            V(i,y) = 0;
        }
    }


     //creating third slit
    for (int y = middle_index-y_s/2-y_s-y_s;y <= middle_index-y_s/2-y_s;y++){
        for (int i = middle_index-x_s/2.;i<=middle_index+x_s/2;i++){
            V(i,y) = 0;
        }
    }
    return V;
}



void Box::write2file(std::string filename, arma::mat V){
    V.save(arma::csv_name(filename));
}
