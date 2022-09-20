#include <dirent.h>
#include <vector>
#include "sloc.hpp"
#include <cstring>
#include <bits/stdc++.h>

namespace sloc {

    runOpts getRunOpts (int argc, char *argv[]) {
    
        runOpts options;

        // Process parameters

        for (int i=2; i < argc; i++) {
                
            if (strcmp(argv[i], "-r") == 0) {
                options.recursive = true;
            } 

            if ((strcmp(argv[i], "-s") == 0) || (strcmp(argv[i], "-S")) == 0) {

                if (strcmp(argv[i], "-S") == 0) {
                    options.ascendOrder = false;
                }

                if (i + 1 < argc) {

                    switch (*(argv[i + 1])) {
                    case 'f':
                        options.order = fileName;
                    case 't':
                        options.order = fileType;
                    case 'c':
                        options.order = comments;
                    case 'b':
                        options.order = blankLines;
                    case 's':
                        options.order = sloc;
                    case 'a':
                        options.order = all;
                    }
                }
            }
        }

        return options;

    } 


/*
std::vector<fileDescrip> getFiles (std::string directory, runOpts is_rec) {

    struct dirent *pDirent;
    DIR *pDir;

    

    // Ensure correct argument count.
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <dirname>\n";
        return EXIT_FAILURE;
    }

    // Ensure we can open directory.
    pDir = opendir(argv[1]);
    if (pDir == NULL) {
        std::cout << "Cannot open directory '" << argv[1] << "'\n";
        return 1;
    }

    // Process each entry.
    while ((pDirent = readdir(pDir)) != NULL) {
        
        std::cout << pDirent->d_name << std::endl;

        std::fstream strm;
        
        strm.open(pDirent->d_name, std::ios_base::in);

        if (strm.is_open()) {            
            
            while (!strm.eof()) {
                char line[100];
                strm.getline(line, 100, '\n');

                std::cout << line << std::endl;

            }

        }
        

        
        std::cout << "[" << pDirent->d_name << "]\n" ;
        std::cout << "\t- <" << pDirent->d_ino << ">\n" ;
        std::cout << "\t- <" << pDirent->d_off << ">\n" ;
        std::cout << "\t- <" << pDirent->d_reclen << ">\n" ;
        std::cout << "\t- <" << pDirent->d_type << ">\n" ; 

        strm.close();

        if (strm.is_open()) {
            std::cout << "ERRO: ARQUIVO AINDA ABERTO" << std::endl;
        }
    }

    // Close directory and exit.
    closedir(pDir);
    return EXIT_SUCCESS;


}
*/

inline bool fName_sorter(fileDescrip F1, fileDescrip F2) {  
    return F1.fileName < F2.fileName;
}
inline bool fComments_sorter(fileDescrip F1, fileDescrip F2){
    return F1.comments < F2.comments;
}
inline bool fBLines_sorter(fileDescrip  F1, fileDescrip F2){
    return F1.blank < F2.blank;
}
inline bool fType_sorter(fileDescrip F1, fileDescrip F2){
    return F1.type < F2.type;
}
inline bool fSloc_sorter(fileDescrip F1, fileDescrip F2){
    return F1.code < F2.code;
}
inline bool fAll_sorter(fileDescrip F1, fileDescrip F2){
    return (F1.code+F1.blank+F1.comments) < (F2.code+F2.blank+F2.comments);
}


std::vector<fileDescrip> sortFiles(std::vector<fileDescrip> files, runOpts order){
    
    // Process parameters
    switch(orderBy){
        case apparition:
        break;
        case fileName:
        std::sort(files.begin(), files.end(), fName_sorter);
        break;
        case fileType:
        std::sort(files.begin(), files.end(), fType_sorter);
        break;
        case comments:
        std::sort(files.begin(), files.end(), fComments_sorter);
        break;
        case blankLines:
        std::sort(files.begin(), files.end(), fBLines_sorter);
        break;
        case sloc:
        std::sort(files.begin(), files.end(), fSloc_sorter);
        break;
        case all:
        std::sort(files.begin(), files.end(), fAll_sorter);
        break;
    }
    return files;
}

}

    


    