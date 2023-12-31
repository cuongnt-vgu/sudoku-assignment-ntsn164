#include "sudoku.h"

int check_box(Cell **box, int num_box_cells, Cell *cell1, Cell *cell2)
{
    // Ensure both cells are within the bounds of the box
    if ((cell1->box_index >= num_box_cells) || (cell2->box_index >= num_box_cells)) {
        return 0;  // Cells are not in the same box
    }

    // Check if both cells are in the same box
    return (cell1->box_index == cell2->box_index);
}
