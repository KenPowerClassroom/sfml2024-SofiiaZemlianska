#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int minesweeper()
{
    srand(time(0));

    RenderWindow window(VideoMode(400, 400), "Minesweeper!");

    int cellSize = 32;
    int mineGrid[12][12];
    int visibleGrid[12][12]; //for showing

    Texture texture;
    texture.loadFromFile("images/minesweeper/tiles.jpg");
    Sprite sprite(texture);

    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        visibleGrid[i][j]=10;
        if (rand()%5==0)  mineGrid[i][j]=9;
        else mineGrid[i][j]=0;
      }

    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        int adjacentMines=0;
        if (mineGrid[i][j]==9) continue;
        if (mineGrid[i+1][j]==9) adjacentMines++;
        if (mineGrid[i][j+1]==9) adjacentMines++;
        if (mineGrid[i-1][j]==9) adjacentMines++;
        if (mineGrid[i][j-1]==9) adjacentMines++;
        if (mineGrid[i+1][j+1]==9) adjacentMines++;
        if (mineGrid[i-1][j-1]==9) adjacentMines++;
        if (mineGrid[i-1][j+1]==9) adjacentMines++;
        if (mineGrid[i+1][j-1]==9) adjacentMines++;
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
              else if (event.key.code == Mouse::Right) visibleGrid[x][y]=11;
        }

        window.clear(Color::White);

        for (int i=1;i<=10;i++)
         for (int j=1;j<=10;j++)
          {
           if (visibleGrid[x][y]==9) visibleGrid[i][j]=mineGrid[i][j];
           sprite.setTextureRect(IntRect(visibleGrid[i][j]*cellSize,0,cellSize,cellSize));
           sprite.setPosition(i*cellSize, j*cellSize);
           window.draw(sprite);
          }

        window.display();
    }

    return 0;
}
