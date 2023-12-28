#include "sudoku.h"

// Add function declarations at the beginning of your file or in your header file
int has_same_candidates(Cell *cell1, Cell *cell2);
int check_box(Cell **box, int num_box_cells, Cell *cell1, Cell *cell2);
int check_candidate(Cell *cell, int value);

int naked_pairs(SudokuBoard *p_board)
{
    int num_changes = 0;

    for (int box_idx = 0; box_idx < BOARD_SIZE; box_idx++)
    {
        Cell **box = p_board->p_boxes[box_idx];
        int num_box_cells = BOARD_SIZE;

        for (int i = 0; i < num_box_cells - 1; i++)
        {
            for (int j = i + 1; j < num_box_cells; j++)
            {
                if (has_same_candidates(box[i], box[j]) && check_box(box, num_box_cells, box[i], box[j]))
                {
                    for (int k = 0; k < BOARD_SIZE * BOARD_SIZE; k++)
                    {
                        Cell *cell = &p_board->data[k / BOARD_SIZE][k % BOARD_SIZE];

                        if (cell != box[i] && cell != box[j])
                        {
                            for (int l = 0; l < cell->num_candidates; l++)
                            {
                                if (check_candidate(box[i], cell->candidates[l]) && check_candidate(box[j], cell->candidates[l]))
                                {
                                    cell->candidates[l] = 0;
                                    cell->num_candidates--;
                                    num_changes++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return num_changes;
}
