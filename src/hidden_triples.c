#include "hidden_singles.h"
#include <stdbool.h>

void find_hidden_single(Cell** p_cells, HiddenSingle* p_hidden_singles, int* p_counter) {
    for (int value = 1; value <= BOARD_SIZE; ++value) {
        int candidate_count = 0;
        Cell* candidate_cell = NULL;

        for (int i = 0; i < BOARD_SIZE; ++i) {
            Cell* cell = p_cells[i];

            if (cell->value != 0) {
                continue; // Skip cells that are already solved
            }

            if (cell->candidates[value - 1] != 0) {
                candidate_count++;
                candidate_cell = cell;
            }
        }

        if (candidate_count == 1) {
            HiddenSingle hidden_single = {candidate_cell->row_index, candidate_cell->col_index, value};
            // Check if the hidden single is already in the list
            bool is_new_hidden_single = true;
            for (int i = 0; i < *p_counter; i++) {
                if (p_hidden_singles[i].row == hidden_single.row &&
                    p_hidden_singles[i].col == hidden_single.col) {
                    is_new_hidden_single = false;
                    break;
                }
            }
            // If not, add it to the list
            if (is_new_hidden_single) {
                p_hidden_singles[*p_counter] = hidden_single;
                (*p_counter)++;
            }
        }
    }
}

void update_board_with_hidden_singles(SudokuBoard* p_board, HiddenSingle* hidden_singles, int total_hidden_singles) {
    for (int i = 0; i < total_hidden_singles; i++) {
        int value = hidden_singles[i].value;
        Cell* cell = &p_board->data[hidden_singles[i].row][hidden_singles[i].col];
        for (int other_value = 1; other_value <= BOARD_SIZE; other_value++) {
            if (other_value != value && cell->candidates[other_value - 1] != 0) {
                cell->candidates[other_value - 1] = 0;
                cell->num_candidates--;
            }
        }
    }
}

int find_and_update_hidden_singles(SudokuBoard* p_board, HiddenSingle* hidden_singles) {
    int total_hidden_singles = 0;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_hidden_single(p_board->p_rows[i], hidden_singles, &total_hidden_singles);
        find_hidden_single(p_board->p_cols[i], hidden_singles, &total_hidden_singles);
        find_hidden_single(p_board->p_boxes[i], hidden_singles, &total_hidden_singles);
    }

    update_board_with_hidden_singles(p_board, hidden_singles, total_hidden_singles);

    return total_hidden_singles;
}
