#pragma once

#include "sudoku.h"

typedef struct HiddenSingle_impl
{
    Cell *p_cell;
    int value;
} HiddenSingle;

// find hidden single cells in a board, return the number of hidden single cells
int hidden_singles(SudokuBoard *p_board);
