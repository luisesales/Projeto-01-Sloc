#include <cstdlib>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include "sloc.hpp"
#include <vector>

int main(int argc, char *argv[]) {
    
    sloc::runOpts runningOpts {};
    std::vector<sloc::fileDescrip> files;

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <dirname>\n";
        return EXIT_FAILURE;
    }

    runningOpts = sloc::getRunOpts(argc, argv);

    std::cout << runningOpts.recursive;

    //files = getFiles(argv[1], runningOptions);

    //files = countFiles(files);

    //files = sortFiles(files, runningOptions);

    //printResult(files);


    return EXIT_SUCCESS;
}