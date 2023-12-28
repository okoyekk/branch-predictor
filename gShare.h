#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "predictors.h"

#pragma once

using namespace std;

class gShare
{
private:
    unsigned long long nCorrect = 0;
    unsigned long long nBranches = 0;
    unsigned long long GHR = 0;
    vector<int> pTable;
    unsigned long long historyMask = 0;

public:
    gShare(int history, vector<branch_line *> &branch_lines, ofstream &outfile);
    ~gShare();
    void updateGHR(int status);
};
