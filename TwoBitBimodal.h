#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "predictors.h"

#pragma once

using namespace std;

class TwoBitBimodal
{
private:
    unsigned long long nCorrect = 0;
    unsigned long long nBranches = 0;
    vector<int> pTable;

public:
    TwoBitBimodal(int table_size, vector<branch_line *> &branch_lines, ofstream &outfile);
    ~TwoBitBimodal();
};
