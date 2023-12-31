#include "naked_triples.h"

int find_naked_triples_values(Cell **p_cells, int *naked_triples_values) {
    int triple_candidates = 0;
    int the_array_of_naked_triples_values[BOARD_SIZE] = {0};
    // Count the occurrences of candidates in the row, avoiding duplicates
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (p_cells[i]->num_candidates > 1) {
            int *candidates = get_candidates(p_cells[i]);
            for (int j = 0; j < p_cells[i]->num_candidates; ++j) {
                int candidate = candidates[j];
                the_array_of_naked_triples_values[candidate - 1]++;
            }
            free(candidates);
        }
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (the_array_of_naked_triples_values[i] >=2) {
            naked_triples_values[triple_candidates++] = i + 1;
        }
    }
  
    return triple_candidates;
}



bool is_naked_triple(Cell *cell1, Cell *cell2, Cell *cell3, int value1, int value2, int value3) {

    if ((cell1->num_candidates <= 3) && (cell2->num_candidates <= 3) && (cell3->num_candidates <= 3) &&
        (cell1->num_candidates >= 2) && (cell2->num_candidates >= 2) && (cell3->num_candidates >= 2)) {

        if ((is_candidate(cell1, value1) || is_candidate(cell1, value2) || is_candidate(cell1, value3)) &&
            (is_candidate(cell2, value1) || is_candidate(cell2, value2) || is_candidate(cell2, value3)) &&
            (is_candidate(cell3, value1) || is_candidate(cell3, value2) || is_candidate(cell3, value3))) {

            // Check if no other values are candidates in these cells
            for (int candidate = 1; candidate <= 9; ++candidate) {
                if ((candidate != value1) && (candidate != value2) && (candidate != value3)) {
                    if (is_candidate(cell1, candidate) || is_candidate(cell2, candidate) || is_candidate(cell3, candidate)) {
                        return false;  // Other value found, not a naked triple
                    }
                }
            }

            return true;  // Naked triple found
        }
    }

    return false;  // No naked triple found
}


void find_naked_triples(Cell **p_cells, NakedTriple *p_naked_triples, int *p_counter) {
    int naked_triples_values[BOARD_SIZE];
    int num_triples = find_naked_triples_values(p_cells, naked_triples_values);

    for (int i = 0; i < num_triples - 2; ++i) {
        for (int k = i + 1; k < num_triples - 1; ++k) {
            for (int l = k + 1; l < num_triples; ++l) {
                for (int j = 0; j < BOARD_SIZE - 2; ++j) {
                    for (int h = j + 1; h < BOARD_SIZE - 1; ++h) {
                        for (int g = h + 1; g < BOARD_SIZE; ++g) {
                            // Check if values are candidates in at least 2 per 3 of the cells
                            if (is_naked_triple(p_cells[j], p_cells[h], p_cells[g], naked_triples_values[i], naked_triples_values[k], naked_triples_values[l])){
                                NakedTriple naked_triple_obj;
                                naked_triple_obj.value1 = naked_triples_values[i];
                                naked_triple_obj.value2 = naked_triples_values[k];
                                naked_triple_obj.value3 = naked_triples_values[l];
                                naked_triple_obj.p_cell1 = p_cells[j];
                                naked_triple_obj.p_cell2 = p_cells[h];
                                naked_triple_obj.p_cell3 = p_cells[g];
                                
                                // Check that if the naked triples is duplicated
                                int duplicate = 0;
                                for (int m = 0; m < *p_counter; ++m) {
                                    if (naked_triple_obj.value1 == p_naked_triples[m].value1 &&
                                        naked_triple_obj.value2 == p_naked_triples[m].value2 &&
                                        naked_triple_obj.value3 == p_naked_triples[m].value3 &&        
                                        naked_triple_obj.p_cell1 == p_naked_triples[m].p_cell1 &&
                                        naked_triple_obj.p_cell2 == p_naked_triples[m].p_cell2 &&
                                        naked_triple_obj.p_cell3 == p_naked_triples[m].p_cell3) {
                                        duplicate = 1;
                                        break;
                                    }
                                }

                                if (!duplicate) {
                                    p_naked_triples[(*p_counter)++] = naked_triple_obj;
                                }                                             
                            }
                        }
                    }
                }
            }
        }
    }    
}

int naked_triples(SudokuBoard *p_board) {
    NakedTriple naked_triples[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;

    // Iterate over rows, columns, and boxes
    for (int i = 0; i < BOARD_SIZE; ++i) {
        find_naked_triples(p_board->p_rows[i], naked_triples, &counter);
        find_naked_triples(p_board->p_cols[i], naked_triples, &counter);
        find_naked_triples(p_board->p_boxes[i], naked_triples, &counter);
    }


    // Iterate over identified naked triples
    for (int i = 0; i < counter; ++i) {
        Cell *naked_triple_cell1 = naked_triples[i].p_cell1;
        Cell *naked_triple_cell2 = naked_triples[i].p_cell2;
        Cell *naked_triple_cell3 = naked_triples[i].p_cell3;
        int value1 = naked_triples[i].value1;
        int value2 = naked_triples[i].value2;
        int value3 = naked_triples[i].value3;

        // Unset candidates in other cells in the same row
        if (naked_triple_cell1->row_index == naked_triple_cell2->row_index &&
            naked_triple_cell1->row_index == naked_triple_cell3->row_index) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
                Cell *current_cell_row = p_board->p_rows[naked_triple_cell1->row_index][j];
            
                if (current_cell_row != naked_triple_cell1 && current_cell_row != naked_triple_cell2 && current_cell_row != naked_triple_cell3) {
                    // Check if the cell has the naked triple values
                    if (is_candidate(current_cell_row, value1)) {
                        unset_candidate(current_cell_row, value1);
                    }
                    if (is_candidate(current_cell_row, value2)) {
                        unset_candidate(current_cell_row, value2);
                    }
                    if (is_candidate(current_cell_row, value3)) {
                        unset_candidate(current_cell_row, value3);
                    }
                }
            }
        }
        
        // Unset candidates in other cells in the same column
        if (naked_triple_cell1->col_index == naked_triple_cell2->col_index &&
            naked_triple_cell1->col_index == naked_triple_cell3->col_index) { 

                    for (int j = 0; j < BOARD_SIZE; ++j) {
                        Cell *current_cell_col = p_board->p_cols[naked_triple_cell1->col_index][j];
                        
                        if (current_cell_col != naked_triple_cell1 && current_cell_col != naked_triple_cell2 && current_cell_col != naked_triple_cell3) {
                            // Check if the cell has the naked triple values
                            if (is_candidate(current_cell_col, value1)) {
                                unset_candidate(current_cell_col, value1);
                            }
                            if (is_candidate(current_cell_col, value2)) {
                                unset_candidate(current_cell_col, value2);
                            }
                            if (is_candidate(current_cell_col, value3)) {
                                unset_candidate(current_cell_col, value3);
                            }
                        }
                    }  
                }


        // Unset candidates in other cells in the same box
        if (naked_triple_cell1->box_index == naked_triple_cell2->box_index &&
            naked_triple_cell1->box_index == naked_triple_cell3->box_index) { 

            for (int j = 0; j < BOARD_SIZE; ++j) {
                Cell *current_cell_box = p_board->p_boxes[naked_triple_cell1->box_index][j];
                
                if (current_cell_box != naked_triple_cell1 && current_cell_box != naked_triple_cell2 && current_cell_box != naked_triple_cell3) {
                    // Check if the cell has the naked triple values
                    if (is_candidate(current_cell_box, value1)) {
                        unset_candidate(current_cell_box, value1);
                    }
                    if (is_candidate(current_cell_box, value2)) {
                        unset_candidate(current_cell_box, value2);
                    }
                    if (is_candidate(current_cell_box, value3)) {
                        unset_candidate(current_cell_box, value3);
                    }
                }
            }  
        }
    }
    
    return (counter);
}
