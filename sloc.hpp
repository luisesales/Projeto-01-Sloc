#pragma once

#include <vector>
#include <string>

namespace sloc {

enum fileExt {
    CPP = 0,
    HPP,
    C,
    H,
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
    fileExt type = CPP;
    unsigned int blank = 0;
    unsigned int code = 0;
    unsigned int comments = 0;
};

// Sort Method of Files Names
bool fName_sorter(fileDescrip const& F1, fileDescrip const& F2);

// Sort Method of Files Comments
bool fComments_sorter(fileDescrip const& F1, fileDescrip const& F2);

// Sort Method of Files Blank Lines
bool fBLines_sorter(fileDescrip const& F1, fileDescrip const& F2);

// Sort Method of Files Types
bool fType_sorter(fileDescrip const& F1, fileDescrip const& F2);

// Save running options given by command line args
runOpts getRunOpts (int argc, char *argv[]);

// Go through files (recursevely or not) and get their info
std::vector<fileDescrip> getFiles (std::string directory, runOpts is_rec);

// Count lines
std::vector<fileDescrip> countLines (std::vector<fileDescrip> files);

// Sort files
std::vector<fileDescrip> sortFiles (std::vector<fileDescrip> files, runOpts order);

// Outputs result on the console
void printResult (std::vector<fileDescrip> sortedFiles);


}
