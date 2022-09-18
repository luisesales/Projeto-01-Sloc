#include <dirent.h>
#include <vector>
#include "sloc.hpp"
#include <cstring>

namespace sloc {

    runOpts getRunOpts (int argc, char *argv[]) {
    
        runOpts options;

        // Process parameters

        for (int i=2; i < argc; i++) {
                
            if (strcmp(argv[i], "-r")) {
                options.recursive = true;
            } 

            if (strcmp(argv[i], "-s") || strcmp(argv[i], "-S")) {

                if (strcmp(argv[i], "-S")) {
                    options.ascendOrder = false;
                }

                if (i + 1 <= argc) {

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


}

    


    