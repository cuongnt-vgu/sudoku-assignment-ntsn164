#include "hidden_pairs.h"
#include "candidates.h"

bool check_pairs(Cell *cells, int size, int num) {
    int pair_count = 0;

    for (int i = 0; i < size; i++) {
        if (cells[i].value == num) {
            pair_count++;
        }
    }

    return pair_count == 2;
}

bool check_pairs_in_list(Cell *p_array, int size, int num) {
    for (int i = 0; i < size; i++) {
        if (p_array[i].value == num) {
            return true;
        }
    }

    return false;
}

int hidden_pairs(SudokuBoard *p_board) {
    int changed_count = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Cell *current_cell = &p_board->data[i][j];

            if (current_cell->value != 0) {
                continue;
            }

            int row_size = BOARD_SIZE;
            int col_size = BOARD_SIZE;
            int box_size = BOARD_SIZE;

            Cell *row_cells = p_board->data[i];
            Cell *col_cells = p_board->data[0] + j;
            Cell *box_cells = &p_board->data[i / BOARD_SIZE * BOARD_SIZE][j / BOARD_SIZE * BOARD_SIZE];

            for (int num = 1; num <= BOARD_SIZE; num++) {
                if (check_pairs(row_cells, row_size, num) && !check_pairs_in_list(col_cells, col_size, num) && !check_pairs_in_list(box_cells, box_size, num)) {
                    remove_candidate(current_cell, num);
                    changed_count++;
                }

                if (check_pairs(col_cells, col_size, num) && !check_pairs_in_list(row_cells, row_size, num) && !check_pairs_in_list(box_cells, box_size, num)) {
                    remove_candidate(current_cell, num);
                    changed_count++;
                }

                if (check_pairs(box_cells, box_size, num) && !check_pairs_in_list(row_cells, row_size, num) && !check_pairs_in_list(col_cells, col_size, num)) {
                    remove_candidate(current_cell, num);
                    changed_count++;
                }
            }
        }
    }

    return changed_count;
}
