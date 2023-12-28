#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#pragma once

using namespace std;

typedef struct branch_line
{
    unsigned long long address;
    int behavior;
    unsigned long long target;
} branch_line;
