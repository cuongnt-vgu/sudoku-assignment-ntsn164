#include "naked_triples.h"

int find_naked_triples_values(SudokuBoard *p_board, int *naked_triples_values) {
    int counter = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Skip cells that are already solved
            if (p_board->data[i][j].value != 0) {
                continue;
            }

            int num_candidates = p_board->data[i][j].num_candidates;
            int *candidates = get_candidates(&p_board->data[i][j]);

            // Check if the cell has exactly 3 candidates
            if (num_candidates == 3) {
                bool foundNakedTriple = true;

                // Check if the candidates of the cell form a naked triple with other cells in the same row, column, or box
                for (int k = 0; k < BOARD_SIZE; k++) {
                    // Skip the current cell
                    if (k == j) {
                        continue;
                    }

                    // Check if the cell has the same candidates as the current cell
                    int *other_candidates = get_candidates(&p_board->data[i][k]);
                    if (other_candidates[0] == candidates[0] && other_candidates[1] == candidates[1] && other_candidates[2] == candidates[2]) {
                        // The candidates form a naked triple with the current cell
                        foundNakedTriple = true;
                    } else {
                        // The candidates do not form a naked triple
                        foundNakedTriple = false;
                        break;
                    }
                }

                if (foundNakedTriple) {
                    naked_triples_values[counter++] = candidates[0];
                    naked_triples_values[counter++] = candidates[1];
                    naked_triples_values[counter++] = candidates[2];
                }
            }
        }
    }

    return counter;
}

void find_naked_triples(SudokuBoard *p_board, NakedTriple *p_naked_triples, int *p_counter) {
    int naked_triples_values[BOARD_SIZE * BOARD_SIZE];
    int num_naked_triples = find_naked_triples_values(p_board, naked_triples_values);

    // Iterate through the naked triple candidates
    for (int i = 0; i < num_naked_triples; i += 3) {
        int value1 = naked_triples_values[i];
        int value2 = naked_triples_values[i + 1];
        int value3 = naked_triples_values[i + 2];

        // Iterate through the cells to find the naked triple
        for (int j = 0; j < BOARD_SIZE; j++) {
            for (int k = 0; k < BOARD_SIZE; k++) {
                // Skip cells that are already solved
                if (p_board->data[j][k].value != 0) {
                    continue;
                }

                int *candidates = get_candidates(&p_board->data[j][k]);

                // Check if the cell has the naked triple candidates
                if (candidates[0] == value1 && candidates[1] == value2 && candidates[2] == value3) {
                    NakedTriple nakedTriple;
                    nakedTriple.p_cell1 = &p_board->data[j][k];
                    nakedTriple.p_cell2 = NULL; // Assign the appropriate Cell pointer
                    nakedTriple.p_cell3 = NULL; // Assign the appropriate Cell pointer

                    p_naked_triples[*p_counter] = nakedTriple;
                    (*p_counter)++;
                }
            }
        }
    }
}