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

    if (runningOpts.recursive) {
        std::cout << "RECURSIVE\n";
    }

    if (!runningOpts.ascendOrder) {
        std::cout << "descending order\n";
    }
    

    //files = getFiles(argv[1], runningOptions);

    //files = countFiles(files);

    //files = sortFiles(files, runningOptions);

    //printResult(files);


    return EXIT_SUCCESS;
}