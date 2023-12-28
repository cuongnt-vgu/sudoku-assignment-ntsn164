#include <stddef.h>
#include "hidden_pairs.h"

void remove_candidate(Cell *cell, int num) {
    // Check if the cell is valid
    if (cell == NULL) {
        // Handle the case of an invalid cell
        return;
    }

    // Check if num is in the valid range
    if (num < 1 || num > BOARD_SIZE) {
        // Handle the case of an invalid num
        return;
    }

    // Check if the cell has candidates
    if (cell->num_candidates > 0) {
        // Check if the candidate to be removed exists
        int index = num - 1;
        if ((cell->candidates[index / 32] & (1 << (index % 32))) != 0) {
            // Remove the candidate by updating the candidates bitmask
            cell->candidates[index / 32] &= ~(1 << (index % 32));
            cell->num_candidates--;
        }
    }
}
