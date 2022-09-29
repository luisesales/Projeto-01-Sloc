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
    else if(argv[1] == "-h" || argv[1] == "--help"){
        {
            sloc::printHelp();
            return EXIT_FAILURE;
        }
    }
    std::vector<sloc::fileDescrip> files;

    sloc::runOpts runningOpts = sloc::getRunOpts(argc, argv);    

    std::string path = "./";
    sloc::getFiles(files, argv[1], runningOpts, path);

    for (int i = 0; i < files.size(); i++) {

        if (files[i].type != sloc::notSupported) {
            std::cout << "Nome: " << files[i].fileName << std::endl;
            std::cout << "Tipo: " << files[i].type << std::endl;
            //std::cout << "Linhas de cód: " << files[i].code << std::endl;
            //std::cout << "linhas de comentário: " << files[i].comments << std::endl;
            //std::cout << "Linhas em branco: " << files[i].blank<< std::endl;
            std::cout << std::endl;
        }

    

    //files = sortFiles(files, runningOptions);

    //printResult(files);


    return EXIT_SUCCESS;
    }
}