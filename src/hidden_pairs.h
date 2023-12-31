#pragma once

#include "sudoku.h"

typedef struct HiddenPairInfo {
    Cell *firstCell;
    Cell *secondCell;
    int firstValue;
    int secondValue;
} HiddenPairInfo;

int locateHiddenPairs(SudokuBoard *board);
void identifyHiddenPairs(Cell **cells, HiddenPairInfo *hiddenPairs, int *pairCount);
int discoverHiddenPairValues(Cell **cells, int *hiddenPairValues);
int detectOverlapInHiddenPairs(HiddenPairInfo *hiddenPairs, int pairCount);


