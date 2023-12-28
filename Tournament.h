#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "predictors.h"

#pragma once

using namespace std;

class Tournament
{
private:
    unsigned long long nCorrect = 0;
    unsigned long long nBranches = 0;

    vector<int> BimodalTable;
    vector<int> gShareTable;
    vector<int> SelectorTable;

    unsigned long long GHR = 0;
    unsigned long long historyMask = int(pow(2, 11)) - 1;

public:
    Tournament(vector<branch_line *> &branch_lines, ofstream &outfile);
    ~Tournament();
    void updateGHR(int status);
};
