// naked_triples.c

#include "naked_triples.h"
bool check_candidate(Cell *cell, int value);

bool find_triple(SudokuBoard *p_board, Cell *p, Cell *q, int value)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Cell *cell = &p_board->data[i][j];

            if (cell != p && cell != q && check_candidate(cell, value))
            {
                return true;
            }
        }
    }

    return false;
}

bool has_candidate(Cell *cell, int value)
{
    return cell->candidates[value - 1] == 1;
}

bool check_candidate(Cell *cell, int value)
{
    return has_candidate(cell, value);
}

bool is_naked_triple(SudokuBoard *p_board, Cell *cell)
{
    int n_values = 0;
    int values[BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (cell->candidates[i] != 0)
        {
            values[n_values++] = cell->candidates[i];
        }
    }

    if (n_values != 3)
    {
        return false;
    }

    for (int i = 0; i < n_values; i++)
    {
        if (!find_triple(p_board, cell, &p_board->data[cell->row_index][cell->col_index], values[i]))
        {
            return false;
        }
    }

    return true;
}

int naked_triples(SudokuBoard *p_board)
{
    int changed = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Cell *cell = &p_board->data[i][j];

            if (is_naked_triple(p_board, cell))
            {
                for (int k = 0; k < BOARD_SIZE; k++)
                {
                    // Ensure the unset_candidate function is declared
                    unset_candidate(cell, k + 1);
                    changed++;
                }
            }
        }
    }

    return changed;
}
