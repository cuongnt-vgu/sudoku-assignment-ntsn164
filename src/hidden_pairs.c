#include "hidden_pairs.h"
#include <string.h>
void unset_candidates_in_box(Cell **box_cells, int *box_candidates, int candidate)
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        if (box_cells[i]->value == 0 && is_candidate(box_cells[i], candidate))
        {
            unset_candidate(box_cells[i], candidate);
        }
    }
}

bool has_hidden_pairs(int *box_candidates)
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        if (box_candidates[i] == HIDDEN_PAIR_CANDIDATES)
        {
            for (int j = i + 1; j < BOARD_SIZE; ++j)
            {
                if (box_candidates[j] == HIDDEN_PAIR_CANDIDATES)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void hidden_pairs(SudokuBoard *p_board)
{
    if (p_board == NULL)
    {
        return;
    }

    for (int box_index = 0; box_index < BOARD_SIZE; ++box_index)
    {
        Cell **box_cells = p_board->p_boxes[box_index];
        int box_candidates[BOARD_SIZE];
        memset(box_candidates, 0, sizeof(box_candidates));

        // Count candidates in the box
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            Cell *cell = box_cells[i];
            if (cell->value == 0)
            {
                for (int j = 0; j < cell->num_candidates; ++j)
                {
                    box_candidates[cell->candidates[j]]++;
                }
            }
        }

        // Check for hidden pairs
        if (has_hidden_pairs(box_candidates))
        {
            for (int k = 0; k < BOARD_SIZE; ++k)
            {
                if (box_candidates[k] == HIDDEN_PAIR_CANDIDATES)
                {
                    unset_candidates_in_box(box_cells, box_candidates, k);
                }
            }

            // Set values for cells with a single candidate
            for (int i = 0; i < BOARD_SIZE; ++i)
            {
                Cell *cell = box_cells[i];
                if (cell->value == 0 && cell->num_candidates == 1)
                {
                    set_candidate(cell, cell->candidates[0]);
                }
            }
        }
    }
}