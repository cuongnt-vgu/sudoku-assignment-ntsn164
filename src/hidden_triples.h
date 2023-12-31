#pragma once

#include "sudoku.h"
typedef struct HiddenTriple_impl
{
    Cell *p_cell1;
    Cell *p_cell2;
    Cell *p_cell3;
    int value1;
    int value2;
    int value3;
} HiddenTriple;

int hidden_triples(SudokuBoard *p_board);
void find_hidden_triples(Cell **p_cells, HiddenTriple *p_hidden_triples, int *p_counter);
int find_hidden_triples_values(Cell **p_cells, int *hidden_triples_values);
int overlaps_hidden_triples(HiddenTriple *p_hidden_triples, int counter);
