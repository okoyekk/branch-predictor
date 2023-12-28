#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "predictors.h"
#include "always_taken.h"
#include "always_not_taken.h"
#include "SingleBitBimodal.h"
#include "TwoBitBimodal.h"
#include "gShare.h"
#include "Tournament.h"

using namespace std;

void load_input_file(string infile_name, vector<branch_line *> &branch_lines)
{
    unsigned long long addr;
    string behavior, line;
    unsigned long long target;
    ifstream infile(infile_name);

    while (infile >> std::hex >> addr >> behavior >> std::hex >> target)
    {
        branch_line *bl = new branch_line;
        bl->address = addr;
        if (behavior == "T")
        {
            bl->behavior = 1;
        }
        else
        {
            bl->behavior = 0;
        }
        bl->target = target;
        branch_lines.push_back(bl);
    }
    infile.close();
}

void BranchTargetBuffer(vector<branch_line *> &branch_lines, ofstream &outfile)
{
    vector<int> BimodalTable = vector<int>(512, 1); // Initialize all table entries to Taken (1)
    vector<unsigned long long> BufferTable = vector<unsigned long long>(512, 0);
    unsigned long long nCorrectPredictions = 0;
    unsigned long long nTotalPredictions = 0;

    for (int i = 0; i < branch_lines.size(); i++)
    {
        if (BimodalTable[branch_lines[i]->address & (512 - 1)] == 1)
        {
            if (BufferTable[branch_lines[i]->address & (512 - 1)] == branch_lines[i]->target)
            {
                nCorrectPredictions++;
            }
            nTotalPredictions++;
        }
        // Set BTB after each prediction to target if branch is taken
        if (branch_lines[i]->behavior)
        {
            BufferTable[branch_lines[i]->address & (512 - 1)] = branch_lines[i]->target;
        }
        // Set Bimodal Table to branch instruction behavior
        BimodalTable[branch_lines[i]->address & (512 - 1)] = branch_lines[i]->behavior;
    }
    outfile << to_string(nCorrectPredictions) << "," << to_string(nTotalPredictions) << ";";
}

int main(int argc, char *argv[])
{
    // check if input is valid
    if (argc != 3)
    {
        cerr << "Usage: ./predictors <input_file> <output_file>" << endl;
        exit(1);
    }

    // Load input files
    vector<branch_line *> branch_lines = vector<branch_line *>();
    load_input_file(argv[1], branch_lines);
    ofstream outfile(argv[2]);

    // Trivial predictor functions
    always_taken(branch_lines, outfile);
    always_not_taken(branch_lines, outfile);
    // Bimodal
    int bimodal_table_sizes[] = {16, 32, 128, 256, 512, 1024, 2048};
    for (auto table_size : bimodal_table_sizes)
    {
        // One Bit Bimodal
        SingleBitBimodal(table_size, branch_lines, outfile);
    }
    outfile << endl;
    for (auto table_size : bimodal_table_sizes)
    {
        // Two Bit Bimodal (Saturating Counters)
        TwoBitBimodal(table_size, branch_lines, outfile);
    }
    outfile << endl;
    // Gshare
    int gshare_history[] = {3, 4, 5, 6, 7, 8, 9, 10, 11};
    for (auto history : gshare_history)
    {
        gShare(history, branch_lines, outfile);
    }
    outfile << endl;
    // Tournament
    Tournament(branch_lines, outfile);
    outfile << endl;
    // BTB
    BranchTargetBuffer(branch_lines, outfile);

    // Free resources
    outfile.close();
    for (auto bl : branch_lines)
    {
        free(bl);
    }
    return 0;
}
