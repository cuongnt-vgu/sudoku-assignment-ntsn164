#pragma once

#include "sudoku.h"

#define HIDDEN_PAIR_CANDIDATES 2  // Replace 2 with the actual value

typedef struct HiddenPairInfo {
    Cell *firstCell;
    Cell *secondCell;
    int firstValue;
    int secondValue;
} HiddenPair;

void hidden_pairs(SudokuBoard *p_board);
