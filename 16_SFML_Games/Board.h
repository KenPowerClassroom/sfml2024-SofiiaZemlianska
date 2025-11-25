#pragma once
#include <cstdlib>

const int GRID_SIZE = 10;
const int BUFFER_SIZE = 12;
const int MINE_VALUE = 9;
const int HIDDEN_CELL = 10;
const int FLAG_CELL = 11;
const int MINE_PROBABILITY = 5;

class Board
{
private:
    int mineGrid[BUFFER_SIZE][BUFFER_SIZE];
    int visibleGrid[BUFFER_SIZE][BUFFER_SIZE];

public:
    Board()
    {
        initializeBoard();
        calculateAdjacentMines();
    }

    void initializeBoard()
    {
        for (int i = 1; i <= GRID_SIZE; i++)
            for (int j = 1; j <= GRID_SIZE; j++)
            {
                visibleGrid[i][j] = HIDDEN_CELL;
                bool shouldPlaceMine = (rand() % MINE_PROBABILITY == 0);
                if (shouldPlaceMine) mineGrid[i][j] = MINE_VALUE;
                else mineGrid[i][j] = 0;
            }
    }

    void calculateAdjacentMines()
    {
        for (int i = 1; i <= GRID_SIZE; i++)
            for (int j = 1; j <= GRID_SIZE; j++)
            {
                int adjacentMines = 0;
                bool currentCellIsMine = (mineGrid[i][j] == MINE_VALUE);
                if (currentCellIsMine) continue;
                if (mineGrid[i + 1][j] == MINE_VALUE) adjacentMines++;
                if (mineGrid[i][j + 1] == MINE_VALUE) adjacentMines++;
                if (mineGrid[i - 1][j] == MINE_VALUE) adjacentMines++;
                if (mineGrid[i][j - 1] == MINE_VALUE) adjacentMines++;
                if (mineGrid[i + 1][j + 1] == MINE_VALUE) adjacentMines++;
                if (mineGrid[i - 1][j - 1] == MINE_VALUE) adjacentMines++;
                if (mineGrid[i - 1][j + 1] == MINE_VALUE) adjacentMines++;
                if (mineGrid[i + 1][j - 1] == MINE_VALUE) adjacentMines++;
                mineGrid[i][j] = adjacentMines;
            }
    }

    void handleCellClick(int x, int y, bool isLeftClick)
    {
        if (x < 1 || x > GRID_SIZE || y < 1 || y > GRID_SIZE)
            return;
        
        if (isLeftClick) visibleGrid[x][y] = mineGrid[x][y];
        else visibleGrid[x][y] = FLAG_CELL;
    }

    void revealAllMines()
    {
        for (int i = 1; i <= GRID_SIZE; i++)
            for (int j = 1; j <= GRID_SIZE; j++)
            {
                visibleGrid[i][j] = mineGrid[i][j];
            }
    }

    int getCellValue(int x, int y)
    {
        if (x < 1 || x > GRID_SIZE || y < 1 || y > GRID_SIZE)
            return HIDDEN_CELL;
        return visibleGrid[x][y];
    }
};
