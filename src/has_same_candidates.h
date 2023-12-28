#include "sudoku.h"

int has_same_candidates(Cell *cell1, Cell *cell2)
{
    if (cell1->num_candidates != cell2->num_candidates) {
        return 0;  // Different number of candidates, not the same
    }

    for (int i = 0; i < cell1->num_candidates; i++) {
        int candidate1 = cell1->candidates[i];
        int found = 0;

        for (int j = 0; j < cell2->num_candidates; j++) {
            if (cell2->candidates[j] == candidate1) {
                found = 1;
                break;
            }
        }

        if (!found) {
            return 0;  // Candidate not found in cell2, not the same
        }
    }

    return 1;  // Same candidates
}
