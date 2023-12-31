#include "hidden_singles.h"
#include <stdbool.h>

#define NULL ((void*)0)

typedef struct {
    int row;
    int col;
    int value;
} HiddenSingles;

void find_hidden_single(Cell** p_cells, HiddenSingles* p_hidden_singles, int* p_counter) {
    for (int value = 1; value <= BOARD_SIZE; ++value) {
        int candidate_count = 0;
        Cell* candidate_cell = NULL;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            Cell* cell = p_cells[i];

            // Skip cells that are already solved
            if (cell->num_candidates == 1) {
                continue;
            }

            // Check if the value is a candidate in the cell
            if (cell->candidates[value - 1] != 0) {
                candidate_count++;
                candidate_cell = cell;
            }
        }

        // If only one cell has the value as a candidate, it's a hidden single
        if (candidate_count == 1) {
            HiddenSingles hidden_single = {
                .row = candidate_cell->row_index,
                .col = candidate_cell->col_index,
                .value = value
            };

            // Store the information about the hidden single cell
            bool new_hidden_single = true;
            for (int i = 0; i < *p_counter; ++i) {
                if (p_hidden_singles[i].row == hidden_single.row &&
                    p_hidden_singles[i].col == hidden_single.col) {
                    new_hidden_single = false;
                    break;
                }
            }

            if (new_hidden_single) {
                p_hidden_singles[*p_counter] = hidden_single;
                (*p_counter)++;
            }
        }
    }
}

int hidden_singles(SudokuBoard* p_board) {
    int total_hidden_singles = 0;
    HiddenSingles hidden_cell[BOARD_SIZE * BOARD_SIZE];

    // Iterate through rows, columns, and boxes to check hidden singles
    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_hidden_single(p_board->p_rows[i], hidden_cell, &total_hidden_singles);
        find_hidden_single(p_board->p_cols[i], hidden_cell, &total_hidden_singles);
        find_hidden_single(p_board->p_boxes[i], hidden_cell, &total_hidden_singles);
    }

    // Update the Sudoku board based on hidden singles
    for (int i = 0; i < total_hidden_singles; ++i) {
        for (int value = 1; value <= 9; ++value) {
            if (value != hidden_cell[i].value) {
                Cell* cell = &p_board->data[hidden_cell[i].row][hidden_cell[i].col];
                if (cell->candidates[value - 1] != 0) {
                    cell->candidates[value - 1] = 0;
                    cell->num_candidates--;
                }
            }
        }
    }

    return total_hidden_singles;
}
