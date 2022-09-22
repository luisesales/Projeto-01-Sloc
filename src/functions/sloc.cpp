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


bool isDirectory (std::string name) {
    int size = name.length();
    auto it = name.rbegin();
    if (size > 2) {
        if (*(it + 1) == '.' or *(it + 2) == '.' or *(it + 3) == '.') {
            return false;
        }
    }
    
    return true;
}

fileExt getType(std::string fileName) {
    int size = fileName.length();
    auto it = fileName.rbegin();
    if (size > 2) {
        if (*(it + 1) == '.') {
            if (*it == 'h') {
                return H;
            } else if (*it == 'c') {
                return C;
            }
        }
        else if (*(it + 3) == '.') {
            if (*it == 'p' and *(it + 1) == 'p' and *(it + 2) == 'c') {
                return CPP;
            } else if (*it == 'p' and *(it + 1) == 'p' and *(it + 2) == 'h') {
                return HPP;
            }
        }
    }

    return notSupported;
}

std::string convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        if (a[i] == '\n') {
            break;
        }
        s = s + a[i];
    }
    return s;
}

void getFiles (std::vector<fileDescrip> &filesVector, char *directory, runOpts is_rec, std::string pathSoFar) {
    std::string line;
    struct dirent *pDirent;
    DIR *pDir;

    // Ensure we can open directory.
    pDir = opendir(directory);
    if (pDir == NULL) {
        std::cout << "Cannot open directory '" << directory << "'\n";
    }

    // Process each entry.
    while ((pDirent = readdir(pDir)) != NULL) {

        if (isDirectory(pDirent->d_name) && is_rec.recursive) {

            std::string name = convertToString((pDirent->d_name), 256);

            getFiles(filesVector, (pDirent->d_name), is_rec, (pathSoFar + "/" + name));
        }

        if (not isDirectory(pDirent->d_name)) {
            fileDescrip description;
            description = countLines(pDirent);
            description.fileName = pathSoFar + pDirent->d_name;
            description.type = getType(pDirent->d_name);

            filesVector.push_back(description);
        }

        
    }

    closedir(pDir);
}



fileDescrip countLines (struct dirent pDirent) {
    std::string line;
    fileDescrip file{"",notSupported,0,0,0};
    bool cMode{false};
    while(std::getline(pDirent,line)){  // Loops for each line in the file 
        
        // Ensure the Line is on Comment Mode
        std::size_t found = line.find("/*");
        if(found != std::string::npos && !cMode){
            if(found > 0){
                file.code++;
            }
            cMode = true;
        }
        if(cMode){
            file.comments++;
            found = line.find("*/")
            if(found != std::string::npos){
                cMode = false;
            }
        }

 
        else{ 

            // Look if there's line comments
            found = line.find("//");
            if(found != std::string::npos){
                file.comments++;
                 if(found > 0){
                    file.code++;
                 }
            }

            // If there's no comments and the size is greater than 0, then there's code
            else if(line.size() > 0){
                file.code++;
            }

            // If the size is 0 and it's not in comment mode, then it is a blank line
            else{
                file.blank++;
            }   
        }
         
    }
    return file;
}




inline bool fName_sorter(const fileDescrip& F1, const fileDescrip& F2) {  
    return F1.fileName < F2.fileName;
}
inline bool fComments_sorter(const fileDescrip& F1, const fileDescrip& F2){
    return F1.comments < F2.comments;
}
inline bool fBLines_sorter(const fileDescrip& F1, const fileDescrip& F2){
    return F1.blank < F2.blank;
}
inline bool fType_sorter(const fileDescrip& F1, const fileDescrip& F2){
    return F1.type < F2.type;
}
inline bool fSloc_sorter(const fileDescrip& F1, const fileDescrip& F2){
    return F1.code < F2.code;
}
inline bool fAll_sorter(const fileDescrip& F1, const fileDescrip& F2){
    return (F1.code+F1.blank+F1.comments) < (F2.code+F2.blank+F2.comments);
}


std::vector<fileDescrip> sortFiles(std::vector<fileDescrip> files, runOpts ordering){
    
    // Process parameters
    switch(ordering.order){
        case apparition:
        break;

        // Order Alphabetically by File Names
        case fileName:
        std::sort(files.begin(), files.end(), fName_sorter);
        break;

        // Order Alphabetically by File Types
        case fileType:
        std::sort(files.begin(), files.end(), fType_sorter);
        break;

        // Order by the numbers of comments of each file from lowest to greatest
        case comments:
        std::sort(files.begin(), files.end(), fComments_sorter);
        break;

        // Order by the numbers of blank lines of each file from lowest to greatest
        case blankLines:
        std::sort(files.begin(), files.end(), fBLines_sorter);
        break;

        // Order by the numbers of code lines of each file from lowest to greatest
        case sloc:
        std::sort(files.begin(), files.end(), fSloc_sorter);
        break;

        // Order by the numbers of total lines of each file from lowest to greatest
        case all:
        std::sort(files.begin(), files.end(), fAll_sorter);
        break;
    }
    return files;
}




}

    


    