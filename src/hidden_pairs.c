#include <stdbool.h>
#include "hidden_pairs.h"

// Implement other necessary functions and structures here

int discoverHiddenPairValues(Cell **cells, int *hiddenPairValues) {
    int pairCandidates = 0;
    int arrayOfHiddenPairValues[BOARD_SIZE] = {0};

    // Count the occurrences of candidates in the row, avoiding duplicates
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (cells[i]->num_candidates > 1) {
            int *candidates = getCandidates(cells[i]);

            for (int j = 0; j < cells[i]->num_candidates; ++j) {
                int candidate = candidates[j];
                arrayOfHiddenPairValues[candidate - 1]++;
            }

            free(candidates);
        }
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (arrayOfHiddenPairValues[i] == 2) {
            hiddenPairValues[pairCandidates++] = i + 1;
        }
    }

    return pairCandidates;
}

void identifyHiddenPairs(Cell **cells, HiddenPairInfo *hiddenPairs, int *pairCount) {
    int hiddenPairValues[BOARD_SIZE];
    int numPairs = discoverHiddenPairValues(cells, hiddenPairValues);

    for (int i = 0; i < numPairs - 1; ++i) {
        for (int k = i + 1; k < numPairs; ++k) {
            // Check if the values are in the same cells
            if (areValuesInSameCells(cells, hiddenPairValues[i], hiddenPairValues[k])) {
                // Check if it is a hidden pair and not a naked pair
                for (int j = 0; j < BOARD_SIZE - 1; j++) {
                    for (int l = j + 1; l < BOARD_SIZE; l++) {
                        if ((isCandidate(cells[j], hiddenPairValues[i]) &&
                             isCandidate(cells[j], hiddenPairValues[k])) &&
                            (isCandidate(cells[l], hiddenPairValues[i]) &&
                             isCandidate(cells[l], hiddenPairValues[k]))) {

                            HiddenPairInfo hiddenPairObj;
                            hiddenPairObj.firstValue = hiddenPairValues[i];
                            hiddenPairObj.secondValue = hiddenPairValues[k];
                            hiddenPairObj.firstCell = cells[j];
                            hiddenPairObj.secondCell = cells[l];
                            hiddenPairs[(*pairCount)++] = hiddenPairObj;
                            break;
                        }
                    }
                }
            }
        }
    }
}

int detectOverlapInHiddenPairs(HiddenPairInfo *hiddenPairs, int pairCount) {
    int overlap = pairCount;

    for (int i = 0; i < pairCount; ++i) {
        int notOverlap = 0;
        Cell *hiddenPairCell1 = hiddenPairs[i].firstCell;
        Cell *hiddenPairCell2 = hiddenPairs[i].secondCell;
        int *candidates1 = getCandidates(hiddenPairCell1);
        int numCandidates = hiddenPairCell1->num_candidates;

        for (int j = 0; j < numCandidates; ++j) {
            if (candidates1[j] != hiddenPairs[i].firstValue && candidates1[j] != hiddenPairs[i].secondValue) {
                unsetCandidate(hiddenPairCell1, candidates1[j]);
                notOverlap = 1;
            }
        }

        free(candidates1);

        int *candidates2 = getCandidates(hiddenPairCell2);
        numCandidates = hiddenPairCell2->num_candidates;

        for (int j = 0; j < numCandidates; ++j) {
            if (candidates2[j] != hiddenPairs[i].firstValue && candidates2[j] != hiddenPairs[i].secondValue) {
                unsetCandidate(hiddenPairCell2, candidates2[j]);
                notOverlap = 1;
            }
        }

        free(candidates2);
        overlap -= notOverlap;
    }

    return overlap;
}

int locateHiddenPairs(SudokuBoard *board) {
    HiddenPairInfo hiddenPairs[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;
    int overlap = 0;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        identifyHiddenPairs(board->p_rows[i], hiddenPairs, &counter);
        identifyHiddenPairs(board->p_cols[i], hiddenPairs, &counter);
        identifyHiddenPairs(board->p_boxes[i], hiddenPairs, &counter);
    }

    overlap = detectOverlapInHiddenPairs(hiddenPairs, counter);
    return (counter - overlap);
}
