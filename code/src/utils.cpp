#include "utils.h"

bool exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}


std::string potential_file(int slit){
    std::string filename;
    switch (slit){
        case 0:
            filename = "no_slit.csv";
            break;
        case 1:
            filename = "single_slit.csv";
            break;
        case 2:
            filename = "double_slit.csv";
            break;
        case 3:
            filename = "triple_slit.csv";
            break;
        default:
            std::cout << "Slit parameter not understood" << std::endl;
    }
    return filename;
}
