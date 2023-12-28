#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "Tournament.h"
#include "predictors.h"

Tournament::Tournament(vector<branch_line *> &branch_lines, ofstream &outfile)
{
    BimodalTable = vector<int>(2048, 3);  // Initialize all table entries to Strongly Taken (3)
    gShareTable = vector<int>(2048, 3);   // Initialize all table entries to Strongly Taken (3)
    SelectorTable = vector<int>(2048, 0); // Initialize all table entries to Strongly Prefer gShare (0)
    unsigned long long index;

    for (int i = 0; i < branch_lines.size(); i++)
    {
        // Check and update Bimodal
        int BimodalStatus = 0;
        if (BimodalTable[branch_lines[i]->address & (2048 - 1)] >= 2 && branch_lines[i]->behavior == 1)
        {
            BimodalStatus = 1;
        }
        if (BimodalTable[branch_lines[i]->address & (2048 - 1)] <= 1 && branch_lines[i]->behavior == 0)
        {
            BimodalStatus = 1;
        }
        if (BimodalTable[branch_lines[i]->address & (2048 - 1)] != 3 && branch_lines[i]->behavior)
        {
            BimodalTable[branch_lines[i]->address & (2048 - 1)]++; // Favor Taken if not Strongly Taken
        }
        if (BimodalTable[branch_lines[i]->address & (2048 - 1)] != 0 && !(branch_lines[i]->behavior))
        {
            BimodalTable[branch_lines[i]->address & (2048 - 1)]--; // Favor NT if not Strongly NT
        }
        // Check and update gShare
        int gShareStatus = 0;
        index = (branch_lines[i]->address ^ GHR) & 2047;
        if (gShareTable[index] >= 2 && branch_lines[i]->behavior)
        {
            gShareStatus = 1;
        }
        if (gShareTable[index] <= 1 && !branch_lines[i]->behavior)
        {
            gShareStatus = 1;
        }
        if (branch_lines[i]->behavior && gShareTable[index] != 3)
        {
            gShareTable[index]++;
        }
        if (!branch_lines[i]->behavior && gShareTable[index] != 0)
        {
            gShareTable[index]--;
        }

        // Make Tournament prediction via selector table
        if (SelectorTable[branch_lines[i]->address & (2048 - 1)] >= 2)
        {
            nCorrect = nCorrect + BimodalStatus;
        }
        if (SelectorTable[branch_lines[i]->address & (2048 - 1)] <= 1)
        {
            nCorrect = nCorrect + gShareStatus;
        }
        // Adjust selector table when bimodal and gshare predictions aren't equal
        if (BimodalStatus != gShareStatus)
        {
            if (BimodalStatus == 1 && gShareStatus == 0)
            { // Favor Bimodal
                if (SelectorTable[branch_lines[i]->address & (2048 - 1)] < 3)
                {
                    SelectorTable[branch_lines[i]->address & (2048 - 1)]++;
                }
            }
            if (BimodalStatus == 0 && gShareStatus == 1)
            { // Favor gShare
                if (SelectorTable[branch_lines[i]->address & (2048 - 1)] > 0)
                {
                    SelectorTable[branch_lines[i]->address & (2048 - 1)]--;
                }
            }
        }

        updateGHR(branch_lines[i]->behavior);
        nBranches++;
    }
    outfile << to_string(nCorrect) << "," << to_string(nBranches) << ";";
}

Tournament::~Tournament()
{
}

void Tournament::updateGHR(int status)
{
    // Makes LSB of GHR the status of the last branch result
    // And GHR only remembers as many bits as history length.
    GHR = GHR << 1;
    GHR = GHR | status;
    GHR = GHR & historyMask;
}
