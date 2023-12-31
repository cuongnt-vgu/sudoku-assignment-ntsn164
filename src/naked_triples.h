#pragma once

#include "sudoku.h"

typedef struct NakedTriple_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    Cell *p_cell3;
    int value1;
    int value2;
    int value3;
} NakedTriple;

int find_naked_triples_values(Cell **p_cells, int *naked_triples_values);
void find_naked_triples(Cell **p_cells, NakedTriple *p_naked_triples, int *p_counter);
int naked_triples(SudokuBoard *p_board);