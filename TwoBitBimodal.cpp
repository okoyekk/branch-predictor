#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TwoBitBimodal.h"
#include "predictors.h"

TwoBitBimodal::TwoBitBimodal(int table_size, vector<branch_line *> &branch_lines, ofstream &outfile)
{
    pTable = vector<int>(table_size, 3); // Initialize all table entries to Strongly Taken (3)
    for (int i = 0; i < branch_lines.size(); i++)
    {
        if (pTable[branch_lines[i]->address & (table_size - 1)] >= 2 && branch_lines[i]->behavior == 1)
        {
            nCorrect++; // Correct prediction (Taken - 2,3)
        }
        if (pTable[branch_lines[i]->address & (table_size - 1)] <= 1 && branch_lines[i]->behavior == 0)
        {
            nCorrect++; // Correct prediction (Not Taken - 0,1)
        }
        if (pTable[branch_lines[i]->address & (table_size - 1)] != 3 && branch_lines[i]->behavior)
        {
            pTable[branch_lines[i]->address & (table_size - 1)]++; // Favor Taken if not Strongly Taken
        }
        if (pTable[branch_lines[i]->address & (table_size - 1)] != 0 && !(branch_lines[i]->behavior))
        {
            pTable[branch_lines[i]->address & (table_size - 1)]--; // Favor NT if not Strongly NT
        }

        nBranches++;
    }
    outfile << to_string(nCorrect) << "," << to_string(nBranches) << ";";
}

TwoBitBimodal::~TwoBitBimodal()
{
}
