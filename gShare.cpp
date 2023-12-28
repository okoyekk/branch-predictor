#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "gShare.h"
#include "predictors.h"

gShare::gShare(int history, vector<branch_line *> &branch_lines, ofstream &outfile)
{
    pTable = vector<int>(2048, 3); // Initialize all table entries to Strongly Taken (3)
    this->historyMask = int(pow(2, history)) - 1;
    unsigned long long index;
    for (int i = 0; i < branch_lines.size(); i++)
    {
        index = (branch_lines[i]->address ^ GHR) & 2047;
        if (pTable[index] >= 2 && branch_lines[i]->behavior)
        {
            nCorrect++;
        }
        if (pTable[index] <= 1 && !branch_lines[i]->behavior)
        {
            nCorrect++;
        }

        if (branch_lines[i]->behavior && pTable[index] != 3)
        {
            pTable[index]++;
        }
        if (!branch_lines[i]->behavior && pTable[index] != 0)
        {
            pTable[index]--;
        }

        updateGHR(branch_lines[i]->behavior);
        nBranches++;
    }

    outfile << to_string(nCorrect) << "," << to_string(nBranches) << ";";
}

gShare::~gShare()
{
}

void gShare::updateGHR(int status)
{
    // Makes LSB of GHR the status of the last branch result
    // And GHR only remembers as many bits as history length.
    GHR = GHR << 1;
    GHR = GHR | status;
    GHR = GHR & historyMask;
}
