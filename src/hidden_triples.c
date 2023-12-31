#include "hidden_triples.h"

bool is_triple(Cell **p_cells, int size)
{
    int candidate = p_cells[0]->value;
    int triple_count = 0;

    for (int i = 0; i < size; i++)
    {
        if (p_cells[i]->value == candidate)
        {
            triple_count++;
        }
    }

    return triple_count == 3;
}

int hidden_triples(SudokuBoard *p_board)
{
    int changed_cells = 0;

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            Cell *p_cells[BOARD_SIZE * BOARD_SIZE];
            int size = 0;

            for (int r = row; r < row + 3 && r < BOARD_SIZE; r++)
            {
                for (int c = col; c < col + 3 && c < BOARD_SIZE; c++)
                {
                    p_cells[size++] = &p_board->data[r][c];
                }
            }

            if (is_triple(p_cells, size))
            {
                int candidate = p_cells[0]->value;

                for (int i = 0; i < size; i++)
                {
                    if (p_cells[i]->value != candidate)
                    {
                        set_candidate(p_cells[i], candidate);
                        changed_cells++;
                    }
                }
            }
        }
    }

    return changed_cells;
}
