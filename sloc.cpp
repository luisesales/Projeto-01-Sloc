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


}
*/

bool fName_sorter(fileDescrip const& F1, fileDescrip const& F2) {
    if(F1.fileName != F2.fileName){
        return F1.fileName < F2.fileName;
    }
}
bool fComments_sorter(fileDescrip const& F1, fileDescrip const& F2){
    return F1.comments < F2.comments;
}
bool fBLines_sorter(fileDescrip const& F1, fileDescrip const& F2){
    return F1.blank < F2.blank;
}
bool fType_sorter(fileDescrip const& F1, fileDescrip const& F2){
    return F1.type < F2.type;
}


std::vector<fileDescrip> sortFiles(std::vector<fileDescrip> files, runOpts order){
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
        break;
        case all:
        break;
    }
    return files;
}

}

    


    