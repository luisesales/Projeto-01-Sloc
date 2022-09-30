#include <cstdlib>
#include <cstring>
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
    else if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
        {
            sloc::printHelp();
            return EXIT_FAILURE;
        }
    }
    std::vector<sloc::fileDescrip> files;

    sloc::runOpts runningOpts = sloc::getRunOpts(argc, argv);    

    std::string path = "./";
    sloc::getFiles(files, argv[1], runningOpts, path);
    
    /*
    for (long unsigned int i = 0; i < files.size(); i++) {

      
            std::cout << "Nome: " << files[i].fileName << std::endl;
            std::cout << "Tipo: " << files[i].type << std::endl;
            std::cout << "Linhas de cód: " << files[i].code << std::endl;
            std::cout << "linhas de comentário: " << files[i].comments << std::endl;
            std::cout << "Linhas em branco: " << files[i].blank<< std::endl;
            std::cout << std::endl;
    }
    */
    

    files = sortFiles(files, runningOpts);

    printResult(files);


    return EXIT_SUCCESS;

}