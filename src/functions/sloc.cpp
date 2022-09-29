#include <dirent.h>
#include <vector>
#include "sloc.hpp"
#include <cstring>
#include <bits/stdc++.h>
#include <string>
#include <fstream>

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
    auto pos = fileName.find('.');
    if (pos != std::string::npos) {

        if (fileName[pos + 1] == 'c' and fileName[pos + 2] == '\0') {
            return C;

        } else if (fileName[pos + 1] == 'h' and fileName[pos + 2] == '\0') {
            return H;

        } else if (fileName[pos + 1] == 'c' and fileName[pos + 2] == 'p' and fileName[pos + 3] == 'p') {
            return CPP;

        } else if (fileName[pos + 1] == 'h' and fileName[pos + 2] == 'p' and fileName[pos + 3] == 'p') {
            return HPP;

        } else {
            return notSupported;

        }
    }

    else return notSupported;
}


std::string convertToString(char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        if (a[i] == '\0') {
            return s;
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

        std::string name = convertToString((pDirent->d_name), 256);

        if (isDirectory(pathSoFar + "/" + name) && is_rec.recursive) {

            getFiles(filesVector, (pDirent->d_name), is_rec, (pathSoFar + "/" + name));
        }

        if (not isDirectory(name)) {
            fileDescrip description;

            //description = countLines(pDirent);
            description.fileName = pathSoFar + name;
            description.type = getType(name);
            
            filesVector.push_back(description);
        }

        
    }

    closedir(pDir);
}

// fileDescrip countLines (struct dirent pDirent) {
//     std::string line;
//     fileDescrip file{"",notSupported,0,0,0};
//     bool cMode{false};
//     while(std::getline(pDirent,line)){  // Loops for each line in the file 
        
//         // Ensure the Line is on Comment Mode
//         std::size_t found = line.find("/*");
//         if(found != std::string::npos && !cMode){
//             if(found > 0){
//                 file.code++;
//             }
//             cMode = true;
//         }
//         if(cMode){
//             file.comments++;
//             found = line.find("*/");
//             if(found != std::string::npos){
//                 cMode = false;
//             }
//         }

 
//         else{ 

//             // Look if there's line comments
//             found = line.find("//");
//             if(found != std::string::npos){
//                 file.comments++;
//                  if(found > 0){
//                     file.code++;
//                  }
//             }

//             // If there's no comments and the size is greater than 0, then there's code
//             else if(line.size() > 0){
//                 file.code++;
//             }

//             // If the size is 0 and it's not in comment mode, then it is a blank line
//             else{
//                 file.blank++;
//             }   
//         }
         
//     }
//     return file;
// }





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

/*
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
*/

void printResult (std::vector<sloc::fileDescrip> sortedFiles) {
    std::vector<unsigned short> columns;
    unsigned short columnIt{0};

    unsigned short consoleLen = 100;
    unsigned short filesProcessed = sortedFiles.size();

    unsigned short fileNameMax{0};
    for (auto i = 0; i < filesProcessed; i++) {
        if (sortedFiles[i].fileName.length() > fileNameMax) {
            fileNameMax = sortedFiles[i].fileName.length();
        }
    }

    std::string c_cpp_header = "C/C++ header";

    std::cout << "Files processed: " << filesProcessed << std::endl;

    for (auto i = 0; i < consoleLen; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;


    std::cout << "Filename";
    columnIt += 9;

    for (auto i = columnIt; i < fileNameMax + 8; i++) {
        std::cout << " ";
    }
    columnIt += fileNameMax - 1;

    columns.push_back(columnIt);
    std::cout << "Language";
    columnIt += 9;

    for (auto i = 0; i < 8; i++) {
        std::cout << " ";
    }
    columnIt += 8;

    columns.push_back(columnIt);
    std::cout << "Comments";
    columnIt += 9;

    for (auto i = 0; i < 10; i++) {
        std::cout << " ";
    }
    columnIt += 10;

    columns.push_back(columnIt);
    std::cout << "Blank";
    columnIt += 6;

    for (auto i = 0; i < 12; i++) {
        std::cout << " ";
    }
    columnIt += 12;

    columns.push_back(columnIt);   
    std::cout << "Code";
    columnIt += 4;

    for (auto i = 0; i < 14; i++) {
        std::cout << " ";
    }
    columnIt += 14;

    columns.push_back(columnIt);   
    std::cout << "All";
    columnIt += 3;

    for (auto i = columnIt; i < 80; i++) {
        std::cout << " ";
    }
    std::cout << std::endl;

    for (auto i = 0; i < consoleLen; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;


    unsigned short commentsSum{0};
    unsigned short blankSum{0};
    unsigned short codeSum{0};
    unsigned short allSum{0};

    columnIt = 0;
    for (int i = 0; i < filesProcessed; i++) {
        std::cout << sortedFiles[i].fileName;
        columnIt += sortedFiles[i].fileName.length();
        for (int j = columnIt; j < columns[0]; j++) {
            std::cout << " ";
        }

        switch (sortedFiles[i].type)
        {
        case sloc::CPP:
            std::cout << "C++";
            break;

        case sloc::C:
            std::cout << "C";
            break;

        case sloc::HPP:
            std::cout << c_cpp_header;
            break;    

        case sloc::H:
            std::cout << c_cpp_header;
            break;      

        default:
            break;
        }



    }


}




}

    


    