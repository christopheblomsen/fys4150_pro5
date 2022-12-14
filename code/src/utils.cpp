#include "utils.h"

// Checks if a file exists in directory
bool exists(const std::string& name) {
    std::ifstream file(name.c_str());
    return file.good();
}

// Used in src/Box.cpp make_file method
// to get the filename for the different slits
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

// Gets the savefile name for the binary file
std::string get_name(std::string filename){
    std::string savefile, tempfile;

    // removes the path from filename
    size_t first_index = filename.find_last_of("/");
    tempfile = filename.substr(first_index + 1, size(filename));

    // removes the .csv and adds .bin
    size_t last_index = tempfile.find_last_of(".");
    savefile = tempfile.substr(0, last_index) + ".bin";
    return savefile;
}
