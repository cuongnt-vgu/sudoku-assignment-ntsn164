#include "naked_pairs.h"

int find_naked_pairs_values(Cell **p_cells, int *hidden_pairs_values) {
    // Initialize the hidden pairs values array
    for (int i = 0; i < BOARD_SIZE; i++) {
        hidden_pairs_values[i] = 0;
    }

    // Count the occurrences of each value in the cells
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Cell *cell = &p_cells[i][j];
            if (cell->value == 0) {
                int *candidates = get_candidates(cell);
                for (int k = 0; k < cell->num_candidates; k++) {
                    hidden_pairs_values[candidates[k] - 1]++;
                }
            }
        }
    }
return 0;}

void find_naked_pairs(Cell **p_cells, NakedPair *p_naked_pairs, int *p_counter) {
    int hidden_pairs_values[BOARD_SIZE];
    find_naked_pairs_values(p_cells, hidden_pairs_values);

    // Find the naked pairs
    for (int value = 1; value <= BOARD_SIZE; value++) {
        if (hidden_pairs_values[value - 1] == 2) {
            Cell *cell1 = NULL;
            Cell *cell2 = NULL;

            // Find the two cells that have the value as a candidate
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    Cell *cell = &p_cells[i][j];
                    if (cell->value == 0 && is_candidate(cell, value)) {
                        if (cell1 == NULL) {
                            cell1 = cell;
                        } else {
                            cell2 = cell;
                            break;
                        }
                    }
                }
                if (cell2 != NULL) {
                    break;
                }
            }

            // Add the naked pair to the array
            p_naked_pairs[*p_counter].p_cell1 = cell1;
            p_naked_pairs[*p_counter].p_cell2 = cell2;
            p_naked_pairs[*p_counter].value1 = value;
            p_naked_pairs[*p_counter].value2 = value;
            (*p_counter)++;
        }
    }
}

int naked_pairs(SudokuBoard *p_board) {
    // Create an array to store the naked pairs
    NakedPair naked_pairs[MAX_PAIRS];
    int counter = 0;

    // Find all the naked pairs in the Sudoku board
    find_naked_pairs(p_board->data, naked_pairs, &counter);

    // Process the naked pairs
    for (int i = 0; i < counter; i++) {
        Cell *cell1 = naked_pairs[i].p_cell1;
        Cell *cell2 = naked_pairs[i].p_cell2;
        int value1 = naked_pairs[i].value1;
        int value2 = naked_pairs[i].value2;

        // Remove the naked pair values from other cells in the same row
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (p_board->p_rows[cell1->row_index][j] != cell1 && p_board->p_rows[cell1->row_index][j] != cell2) {
                unset_candidate(p_board->p_rows[cell1->row_index][j], value1);
                unset_candidate(p_board->p_rows[cell1->row_index][j], value2);
            }
        }

        // Remove the naked pair values from other cells in the same column
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (p_board->p_cols[cell1->col_index][j] != cell1 && p_board->p_cols[cell1->col_index][j] != cell2) {
                unset_candidate(p_board->p_cols[cell1->col_index][j], value1);
                unset_candidate(p_board->p_cols[cell1->col_index][j], value2);
            }
        }
    }

    return counter;
}
