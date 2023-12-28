#include <iostream>
#include <fstream>
#include <string>

#include "predictors.h"

#pragma once

using namespace std;

void always_not_taken(vector<branch_line *> &branch_lines, ofstream &outfile)
{
    unsigned long long nCorrect = 0;
    unsigned long long nBranches = 0;

    for (auto bl : branch_lines)
    {
        if (bl->behavior == 0)
        {
            nCorrect++;
        }
        nBranches++;
    }

    outfile << to_string(nCorrect) << "," << to_string(nBranches) << ";" << endl;
}
