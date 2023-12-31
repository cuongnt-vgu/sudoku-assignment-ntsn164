#include "hidden_triples.h"

// Function to check if an array of cells contains a hidden triple
bool is_triple(Cell **p_cells, int size) {
    int candidate = p_cells[0]->value;
    int triple_count = 0;

    for (int i = 0; i < size; i++) {
        if (p_cells[i]->value == candidate) {
            triple_count++;
        }
    }

    return triple_count == 3;
}

// Function to find and eliminate hidden triples in a Sudoku board
int hidden_triples(SudokuBoard *p_board) {
    int changed_cells = 0;

    // Iterate over each 3x3 block in the Sudoku board
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            Cell *p_cells[BOARD_SIZE * BOARD_SIZE];
            int size = 0;

            // Collect cells in the current 3x3 block into an array
            for (int r = row; r < row + 3 && r < BOARD_SIZE; r++) {
                for (int c = col; c < col + 3 && c < BOARD_SIZE; c++) {
                    p_cells[size++] = &p_board->data[r][c];
                }
            }

            // Check if the collected cells form a hidden triple
            if (is_triple(p_cells, size)) {
                int candidate = p_cells[0]->value;

                // Remove the candidate from other cells in the block
                for (int i = 0; i < size; i++) {
                    if (p_cells[i]->value != candidate) {
                        // Assuming remove_candidate is a function to eliminate a candidate
                        if (remove_candidate(p_cells[i], candidate)) {
                            changed_cells++;
                        }
                    }
                }
            }
        }
    }

    // Return the total number of changed cells
    return changed_cells;
}
