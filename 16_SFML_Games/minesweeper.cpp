#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int minesweeper()
{
    srand(time(0));

    const int GRID_SIZE = 10;
    const int BUFFER_SIZE = 12;
    const int CELL_SIZE = 32;
    const int WINDOW_SIZE = 400;
    const int MINE_VALUE = 9;
    const int HIDDEN_CELL = 10;
    const int FLAG_CELL = 11;
    const int MINE_PROBABILITY = 5;

    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Minesweeper!");

    int cellSize = CELL_SIZE;
    int mineGrid[BUFFER_SIZE][BUFFER_SIZE];
    int visibleGrid[BUFFER_SIZE][BUFFER_SIZE]; //for showing

    Texture texture;
    texture.loadFromFile("images/minesweeper/tiles.jpg");
    Sprite sprite(texture);

    for (int i=1;i<=GRID_SIZE;i++)
     for (int j=1;j<=GRID_SIZE;j++)
      {
        visibleGrid[i][j]=HIDDEN_CELL;
        if (rand()%MINE_PROBABILITY==0)  mineGrid[i][j]=MINE_VALUE;
        else mineGrid[i][j]=0;
      }

    for (int i=1;i<=GRID_SIZE;i++)
     for (int j=1;j<=GRID_SIZE;j++)
      {
        int adjacentMines=0;
        if (mineGrid[i][j]==MINE_VALUE) continue;
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

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x/cellSize;
        int y = pos.y/cellSize;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
              if (event.key.code == Mouse::Left) visibleGrid[x][y]=mineGrid[x][y];
              else if (event.key.code == Mouse::Right) visibleGrid[x][y]=FLAG_CELL;
        }

        window.clear(Color::White);

        for (int i=1;i<=GRID_SIZE;i++)
         for (int j=1;j<=GRID_SIZE;j++)
          {
           if (visibleGrid[x][y]==MINE_VALUE) visibleGrid[i][j]=mineGrid[i][j];
           sprite.setTextureRect(IntRect(visibleGrid[i][j]*cellSize,0,cellSize,cellSize));
           sprite.setPosition(i*cellSize, j*cellSize);
           window.draw(sprite);
          }

        window.display();
    }

    return 0;
}
