#include <cstdlib>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include "functions/sloc.hpp"
#include <vector>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <dirname>\n";
        return EXIT_FAILURE;
    }
    
    std::vector<sloc::fileDescrip> files;

    sloc::runOpts runningOpts = sloc::getRunOpts(argc, argv);    

    std::string path = "";
    sloc::getFiles(files, argv[1], runningOpts, path);

    //files = countFiles(files);

    //files = sortFiles(files, runningOptions);

    //printResult(files);


    return EXIT_SUCCESS;
}