#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int GRID_SIZE = 10;
const int BUFFER_SIZE = 12;
const int CELL_SIZE = 32;
const int WINDOW_SIZE = 400;
const int MINE_VALUE = 9;
const int HIDDEN_CELL = 10;
const int FLAG_CELL = 11;
const int MINE_PROBABILITY = 5;

void initializeGame(int mineGrid[BUFFER_SIZE][BUFFER_SIZE], int visibleGrid[BUFFER_SIZE][BUFFER_SIZE])
{
    for (int i=1;i<=GRID_SIZE;i++)
     for (int j=1;j<=GRID_SIZE;j++)
      {
        visibleGrid[i][j]=HIDDEN_CELL;
        bool shouldPlaceMine = (rand()%MINE_PROBABILITY==0);
        if (shouldPlaceMine)  mineGrid[i][j]=MINE_VALUE;
        else mineGrid[i][j]=0;
      }
}

void calculateAdjacentMines(int mineGrid[BUFFER_SIZE][BUFFER_SIZE])
{
    for (int i=1;i<=GRID_SIZE;i++)
     for (int j=1;j<=GRID_SIZE;j++)
      {
        int adjacentMines=0;
        bool currentCellIsMine = (mineGrid[i][j]==MINE_VALUE);
        if (currentCellIsMine) continue;
        if (mineGrid[i+1][j]==MINE_VALUE) adjacentMines++;
        if (mineGrid[i][j+1]==MINE_VALUE) adjacentMines++;
        if (mineGrid[i-1][j]==MINE_VALUE) adjacentMines++;
        if (mineGrid[i][j-1]==MINE_VALUE) adjacentMines++;
        if (mineGrid[i+1][j+1]==MINE_VALUE) adjacentMines++;
        if (mineGrid[i-1][j-1]==MINE_VALUE) adjacentMines++;
        if (mineGrid[i-1][j+1]==MINE_VALUE) adjacentMines++;
        if (mineGrid[i+1][j-1]==MINE_VALUE) adjacentMines++;
        mineGrid[i][j]=adjacentMines;
      }
}

void loadResources(Texture& texture, Sprite& sprite)
{
    texture.loadFromFile("images/minesweeper/tiles.jpg");
    sprite.setTexture(texture);
}

void handleInput(RenderWindow& window, Event& event, int visibleGrid[BUFFER_SIZE][BUFFER_SIZE], 
                 int mineGrid[BUFFER_SIZE][BUFFER_SIZE], int x, int y)
{
    if (event.type == Event::Closed)
        window.close();

    if (event.type == Event::MouseButtonPressed)
    {
      bool isLeftClick = (event.key.code == Mouse::Left);
      bool isRightClick = (event.key.code == Mouse::Right);
      
      if (isLeftClick) visibleGrid[x][y]=mineGrid[x][y];
      else if (isRightClick) visibleGrid[x][y]=FLAG_CELL;
    }
}

void updateGameState(int visibleGrid[BUFFER_SIZE][BUFFER_SIZE], int mineGrid[BUFFER_SIZE][BUFFER_SIZE], int x, int y)
{
    bool mineWasClicked = (visibleGrid[x][y]==MINE_VALUE);
    if (mineWasClicked)
    {
        for (int i=1;i<=GRID_SIZE;i++)
         for (int j=1;j<=GRID_SIZE;j++)
          {
            visibleGrid[i][j]=mineGrid[i][j];
          }
    }
}

void renderGame(RenderWindow& window, Sprite& sprite, int visibleGrid[BUFFER_SIZE][BUFFER_SIZE], int cellSize)
{
    window.clear(Color::White);

    for (int i=1;i<=GRID_SIZE;i++)
     for (int j=1;j<=GRID_SIZE;j++)
      {
       int cellValue = visibleGrid[i][j];
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

    int cellSize = CELL_SIZE;
    int mineGrid[BUFFER_SIZE][BUFFER_SIZE];
    int visibleGrid[BUFFER_SIZE][BUFFER_SIZE]; //for showing

    Texture texture;
    Sprite sprite;
    loadResources(texture, sprite);

    initializeGame(mineGrid, visibleGrid);
    calculateAdjacentMines(mineGrid);

    while (window.isOpen())
    {
        Vector2i mousePosition = Mouse::getPosition(window);
        int gridX = mousePosition.x / cellSize;
        int gridY = mousePosition.y / cellSize;

        Event event;
        while (window.pollEvent(event))
        {
            handleInput(window, event, visibleGrid, mineGrid, gridX, gridY);
        }

        updateGameState(visibleGrid, mineGrid, gridX, gridY);
        renderGame(window, sprite, visibleGrid, cellSize);
    }

    return 0;
}
