#include "pch.h"
#include "../16_SFML_Games/Board.h"

TEST(BoardTest, AllCellsStartHidden)
{
    Board board;

    for (int i = 1; i <= GRID_SIZE; i++) {
        for (int j = 1; j <= GRID_SIZE; j++) {
            EXPECT_EQ(HIDDEN_CELL, board.getCellValue(i, j));
        }
    }

    EXPECT_EQ(HIDDEN_CELL, board.getCellValue(0, 5));
    EXPECT_EQ(HIDDEN_CELL, board.getCellValue(5, 0));
    EXPECT_EQ(HIDDEN_CELL, board.getCellValue(-1, -1));
}

TEST(BoardTest, LeftClickRevealsCorrectValue)
{
    Board board;

    board.handleCellClick(3, 3, true);

    int value = board.getCellValue(3, 3);

    bool valid =
        value == 0 || value == 1 || value == 2 || value == 3 || value == 4 ||
        value == 5 || value == 6 || value == 7 || value == 8 || value == MINE_VALUE;

    EXPECT_EQ(true, valid);
}

TEST(BoardTest, RightClickPlacesFlag)
{
    Board board;

    board.handleCellClick(5, 5, false);
    EXPECT_EQ(FLAG_CELL, board.getCellValue(5, 5));

    board.handleCellClick(3, 3, false);
    EXPECT_EQ(FLAG_CELL, board.getCellValue(3, 3));
}

TEST(BoardTest, RevealAllShowsEverything)
{
    Board board;

    board.revealAllMines();

    for (int i = 1; i <= GRID_SIZE; i++)
        for (int j = 1; j <= GRID_SIZE; j++)
        {
            int value = board.getCellValue(i, j);
            bool valid =
                value == 0 || value == 1 || value == 2 || value == 3 || value == 4 ||
                value == 5 || value == 6 || value == 7 || value == 8 || value == MINE_VALUE;

            EXPECT_EQ(true, valid);
        }
}

TEST(BoardTest, ClickOutsideBoardDoesNothing)
{
    Board board;

    board.handleCellClick(0, 0, true);
    board.handleCellClick(20, 20, true);

    for (int i = 1; i <= GRID_SIZE; i++)
        for (int j = 1; j <= GRID_SIZE; j++)
            EXPECT_EQ(HIDDEN_CELL, board.getCellValue(i, j));
}

TEST(BoardTest, AdjacentMineCountWithinValidRange)
{
    Board board;

    board.revealAllMines();

    for (int i = 1; i <= GRID_SIZE; i++)
        for (int j = 1; j <= GRID_SIZE; j++)
        {
            int value = board.getCellValue(i, j);
            bool valid =
                value == 0 || value == 1 || value == 2 || value == 3 || value == 4 ||
                value == 5 || value == 6 || value == 7 || value == 8 || value == MINE_VALUE;

            EXPECT_EQ(true, valid);
        }
}