#include <iostream>

#include "SFML/Graphics.hpp"
#include "./Playfield/Playfield.hpp"


#include "./Tetrimino/Tetrimino.hpp"

const int SF_WINDOW_WIDTH = 1000;
const int SF_WINDOW_HEIGHT = 1000;

int main()
{
    TetrisEngine::Playfield pf = TetrisEngine::Playfield(SF_WINDOW_WIDTH / TetrisEngine::DEFAULT_PLAYFIELD.y);

    sf::RenderWindow window(sf::VideoMode(SF_WINDOW_WIDTH, SF_WINDOW_HEIGHT), "Tetris...");
    window.setFramerateLimit(30);

    auto tet = TetrisEngine::Tetrimino(TetrisEngine::J,TetrisEngine::TetriminosColors::J);

    pf.AddTetrimino(tet);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
                pf.HandleEvent(event.key.code);
        }

        window.clear();
        pf.Update();
        window.draw(pf);
        window.display();
    }

    return 0;
}