#pragma once

#include <vector>
#include <string>

namespace sloc {

enum fileExt {
    CPP = 0,
    HPP,
    C,
    H,
    notSupported,
};


enum orderBy {
    apparition = 0,
    fileName,
    fileType,
    comments,
    blankLines,
    sloc,
    all,
};


struct runOpts {
    bool recursive = false;
    bool ascendOrder = true;
    int order = apparition;
};


struct fileDescrip {
    std::string fileName = "";
    fileExt type = notSupported;
    unsigned int blank = 0;
    unsigned int code = 0;
    unsigned int comments = 0;
    unsigned int total = 0;
};

// Go through files (recursevely or not) and get their info
void getFiles (std::vector<fileDescrip> &filesVector, 
char * directory, runOpts is_rec, std::string pathSoFar);

// Count lines
fileDescrip countLines (struct dirent pDirent);

// Sort Method of Files Names
inline bool fName_sorter(const fileDescrip& F1, const fileDescrip& F2);

// Sort Method of Files Comments
inline bool fComments_sorter(const fileDescrip& F1, const fileDescrip& F2);

// Sort Method of Files Blank Lines
inline bool fBLines_sorter(const fileDescrip& F1, const fileDescrip& F2);

// Sort Method of Files Types
inline bool fType_sorter(const fileDescrip& F1, const fileDescrip& F2);

//Sort Method of Code Lines
inline bool fSloc_sorter(const fileDescrip& F1, const fileDescrip& F2);

//Sort Method of Sum of all Lines
inline bool fAll_sorter(const fileDescrip& F1, const fileDescrip& F2);

// Save running options given by command line args
runOpts getRunOpts (int argc, char *argv[]);

// Sort files
std::vector<fileDescrip> sortFiles (std::vector<fileDescrip> files, runOpts order);

// Outputs result on the console
void printResult (std::vector<fileDescrip> sortedFiles);


}
