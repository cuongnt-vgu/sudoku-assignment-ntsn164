#include "hidden_singles.h"
#include <stddef.h>
#include <stdbool.h>

// Function to find hidden single cells in the Sudoku board
void find_hidden_single(Cell **p_cells, HiddenSingle *p_hidden_singles, int *p_counter) {
    // Iterate through each value (1 to BOARD_SIZE) to find hidden singles
    for (int value = 1; value <= BOARD_SIZE; ++value) {
        // Check if the value is a candidate in only one cell
        int candidate_count = 0;
        Cell *candidate_cell = NULL;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            Cell *cell = p_cells[i];

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
            HiddenSingle hidden_single;
            hidden_single.p_cell = candidate_cell;
            hidden_single.value = value;

            // Store the information about the hidden single cell
            bool new_hidden_single = true;
            for (int i = 0; i < *p_counter; i++) {
                if (p_hidden_singles[i].p_cell == hidden_single.p_cell) {
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

// Function to find hidden single cells in a Sudoku board
int hidden_singles(SudokuBoard *p_board) {
    int total_hidden_singles = 0;
    HiddenSingle hidden_cell[BOARD_SIZE * BOARD_SIZE];

    // Iterate through rows and check hidden singles
    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_hidden_single(p_board->p_rows[i], hidden_cell, &total_hidden_singles);
    }

    // Iterate through columns and check hidden singles
    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_hidden_single(p_board->p_cols[i], hidden_cell, &total_hidden_singles);
    }

    // Iterate through boxes and check hidden singles
    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_hidden_single(p_board->p_boxes[i], hidden_cell, &total_hidden_singles);
    }

    // Update the candidates in the board based on the hidden singles
    for (int i = 0; i < total_hidden_singles; i++) {
        HiddenSingle hidden_single = hidden_cell[i];
        int value = hidden_single.value;

        // Update candidates in the row, column, and box
        for (int j = 0; j < BOARD_SIZE; j++) {
            Cell *cell = hidden_single.p_cell;
            if (cell->candidates[value - 1] != 0) {
                cell->candidates[value - 1] = 0;
                cell->num_candidates--;
            }
        }
    }

    return total_hidden_singles;
}
