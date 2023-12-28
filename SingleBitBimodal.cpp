#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "SingleBitBimodal.h"
#include "predictors.h"

SingleBitBimodal::SingleBitBimodal(int table_size, vector<branch_line *> &branch_lines, ofstream &outfile)
{
    pTable = vector<int>(table_size, 1); // Initialize all table entries to Taken (1)
    for (int i = 0; i < branch_lines.size(); i++)
    {
        if (pTable[branch_lines[i]->address & (table_size - 1)] == branch_lines[i]->behavior)
        {
            nCorrect++; // Correct prediction
        }
        pTable[branch_lines[i]->address & (table_size - 1)] = branch_lines[i]->behavior;

        nBranches++;
    }
    outfile << to_string(nCorrect) << "," << to_string(nBranches) << ";";
}

SingleBitBimodal::~SingleBitBimodal()
{
}
