#include <SFML/Graphics.hpp>
#include <time.h>
#include "Board.h"
using namespace sf;

const int CELL_SIZE = 32;
const int WINDOW_SIZE = 400;

void loadResources(Texture& texture, Sprite& sprite)
{
    texture.loadFromFile("images/minesweeper/tiles.jpg");
    sprite.setTexture(texture);
}

void handleInput(RenderWindow& window, Event& event, Board& board, int x, int y)
{
    if (event.type == Event::Closed)
        window.close();
    if (event.type == Event::MouseButtonPressed)
    {
      bool isLeftClick = (event.key.code == Mouse::Left);
      bool isRightClick = (event.key.code == Mouse::Right);
      
      if (isLeftClick || isRightClick) 
      {
          board.handleCellClick(x, y, isLeftClick);
      }
    }
}

void updateGameState(Board& board, int x, int y)
{
    bool mineWasClicked = (board.getCellValue(x, y) == MINE_VALUE);
    if (mineWasClicked)
    {
        board.revealAllMines();
    }
}

void renderGame(RenderWindow& window, Sprite& sprite, Board& board, int cellSize)
{
    window.clear(Color::White);

    for (int i=1;i<=GRID_SIZE;i++)
     for (int j=1;j<=GRID_SIZE;j++)
      {
       int cellValue = board.getCellValue(i, j);
       int textureXOffset = cellValue * cellSize;
       int spriteXPosition = i * cellSize;
       int spriteYPosition = j * cellSize;
       
       sprite.setTextureRect(IntRect(textureXOffset, 0, cellSize, cellSize));
       sprite.setPosition(spriteXPosition, spriteYPosition);
       window.draw(sprite);
      }
    window.display();
}

int minesweeper()
{
    srand(time(0));

    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Minesweeper!");
    Board board;

    int cellSize = CELL_SIZE;

    Texture texture;
    Sprite sprite;
    loadResources(texture, sprite);

    while (window.isOpen())
    {
        Vector2i mousePosition = Mouse::getPosition(window);
        int gridX = mousePosition.x / cellSize;
        int gridY = mousePosition.y / cellSize;

        Event event;
        while (window.pollEvent(event))
        {
            handleInput(window, event, board, gridX, gridY);
        }

        updateGameState(board, gridX, gridY);
        renderGame(window, sprite, board, cellSize);
    }
    return 0;
}
