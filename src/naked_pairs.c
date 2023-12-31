#include "naked_pairs.h"

int find_naked_pairs_values(Cell **p_cells, int *naked_pairs_values) {
    int pair_candidates = 0;
    int the_array_of_naked_pairs_values[BOARD_SIZE] = {0};
    // Count the occurrences of candidates in the row, avoiding duplicates
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (p_cells[i]->num_candidates > 1) {
            int *candidates = get_candidates(p_cells[i]);
            for (int j = 0; j < p_cells[i]->num_candidates; ++j) {
                int candidate = candidates[j];
                the_array_of_naked_pairs_values[candidate - 1]++;
            }
            free(candidates);
        }
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (the_array_of_naked_pairs_values[i] >=2) {
            naked_pairs_values[pair_candidates++] = i + 1;
        }
    }
  
    return pair_candidates;
}

bool is_naked_pair(Cell *cell1, Cell *cell2, int value1, int value2) {
    // Check if both cells have only two candidates
    if ((cell1->num_candidates == 2) && (cell2->num_candidates == 2)) {
        // Check if the candidates in both cells are the same
        if (is_candidate(cell1, value1) && is_candidate(cell2, value1) && is_candidate(cell1, value2) && is_candidate(cell2, value2))  {
            return true;  // Naked pair found
        }
    }
    return false;  // No naked pair found
}
void find_naked_pairs(Cell **p_cells, NakedPair *p_naked_pairs, int *p_counter) {
    int naked_pairs_values[BOARD_SIZE];
    int num_pairs = find_naked_pairs_values(p_cells, naked_pairs_values);

    for (int i = 0; i < num_pairs - 1; ++i) {
        for (int k = i + 1; k < num_pairs; ++k) {
            for (int j = 0; j < BOARD_SIZE - 1; j++) {
                for (int l = j + 1; l < BOARD_SIZE; l++) {
                    // Check if naked cells
                    if (is_naked_pair(p_cells[j], p_cells[l], naked_pairs_values[i], naked_pairs_values[k])) {
                        if ((is_candidate(p_cells[j], naked_pairs_values[i]) &&
                             is_candidate(p_cells[j], naked_pairs_values[k])) &&
                            (is_candidate(p_cells[l], naked_pairs_values[i]) &&
                             is_candidate(p_cells[l], naked_pairs_values[k]))) {
                            NakedPair naked_pair_obj;
                            naked_pair_obj.value1 = naked_pairs_values[i];
                            naked_pair_obj.value2 = naked_pairs_values[k];
                            naked_pair_obj.p_cell1 = p_cells[j];
                            naked_pair_obj.p_cell2 = p_cells[l];

                            // Check if this naked pair has already been processed
                            int duplicate = 0;
                            for (int m = 0; m < *p_counter; ++m) {
                                if (naked_pair_obj.value1 == p_naked_pairs[m].value1 &&
                                    naked_pair_obj.value2 == p_naked_pairs[m].value2 &&
                                    naked_pair_obj.p_cell1 == p_naked_pairs[m].p_cell1 &&
                                    naked_pair_obj.p_cell2 == p_naked_pairs[m].p_cell2) {
                                    duplicate = 1;
                                    break;
                                }
                            }

                            if (!duplicate) {
                                p_naked_pairs[(*p_counter)++] = naked_pair_obj;
                            }
                        }
                    }
                }
            }
        }
    }
}

int naked_pairs(SudokuBoard *p_board) {
    NakedPair naked_pairs[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;
    // Iterate over rows, columns, and boxes
    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_naked_pairs(p_board->p_rows[i], naked_pairs, &counter);
        find_naked_pairs(p_board->p_cols[i], naked_pairs, &counter);
        find_naked_pairs(p_board->p_boxes[i], naked_pairs, &counter);
    }


    // Iterate over identified naked pairs
    for (int i = 0; i < counter; ++i) {
        Cell *naked_pair_cell1 = naked_pairs[i].p_cell1;
        Cell *naked_pair_cell2 = naked_pairs[i].p_cell2;
        int value1 = naked_pairs[i].value1;
        int value2 = naked_pairs[i].value2;

        // Unset candidates in other cells in the same row
        if (naked_pair_cell1->row_index == naked_pair_cell2->row_index) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
                Cell *current_cell_row = p_board->p_rows[naked_pair_cell1->row_index][j];
            
                if (current_cell_row != naked_pair_cell1 && current_cell_row != naked_pair_cell2) {
                    // Check if the cell has the naked pair values
                    if (is_candidate(current_cell_row, value1)) {
                        unset_candidate(current_cell_row, value1);
                    }
                    if (is_candidate(current_cell_row, value2)) {
                        unset_candidate(current_cell_row, value2);
                    }
                    
                }
            }
        }
        
        // Unset candidates in other cells in the same column
        if (naked_pair_cell1->col_index == naked_pair_cell2->col_index) { 

                    for (int j = 0; j < BOARD_SIZE; ++j) {
                        Cell *current_cell_col = p_board->p_cols[naked_pair_cell1->col_index][j];
                        
                        if (current_cell_col != naked_pair_cell1 && current_cell_col != naked_pair_cell2) {
                            // Check if the cell has the naked pair values
                            if (is_candidate(current_cell_col, value1)) {
                                unset_candidate(current_cell_col, value1);
                            }
                            if (is_candidate(current_cell_col, value2)) {
                                unset_candidate(current_cell_col, value2);
                            }
                        }
                    }  
                }


        // Unset candidates in other cells in the same box
        if (naked_pair_cell1->box_index == naked_pair_cell2->box_index) { 

            for (int j = 0; j < BOARD_SIZE; ++j) {
                Cell *current_cell_box = p_board->p_boxes[naked_pair_cell1->box_index][j];
                
                if (current_cell_box != naked_pair_cell1 && current_cell_box != naked_pair_cell2) {
                    // Check if the cell has the naked pair values
                    if (is_candidate(current_cell_box, value1)) {
                        unset_candidate(current_cell_box, value1);
                    }
                    if (is_candidate(current_cell_box, value2)) {
                        unset_candidate(current_cell_box, value2);
                    }
                }
            }  
        }
    }
    
    return (counter);
}
