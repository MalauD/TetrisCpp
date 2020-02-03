#include <iostream>
#include <sstream>

#include "SFML/Graphics.hpp"
#include "./Playfield/Playfield.hpp"


#include "./Tetrimino/Tetrimino.hpp"

const int SF_WINDOW_WIDTH = 1000;
const int SF_WINDOW_HEIGHT = 1000;

std::string toString(int integer)
{
    std::ostringstream os;
    os << "Score : " << integer;
    return os.str();
}

int main()
{
    TetrisEngine::Playfield pf = TetrisEngine::Playfield(SF_WINDOW_WIDTH / TetrisEngine::DEFAULT_PLAYFIELD.y);

    sf::RenderWindow window(sf::VideoMode(SF_WINDOW_WIDTH, SF_WINDOW_HEIGHT), "Tetris...");
    window.setFramerateLimit(60);

    
    pf.AddTetrimino(TetrisEngine::Tetrimino::GetRandom());

    sf::Clock cl;

    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text scoreTxt;
    scoreTxt.setFont(font);
    scoreTxt.setCharacterSize(24);
    scoreTxt.setFillColor(sf::Color::White);
    scoreTxt.setPosition(SF_WINDOW_WIDTH / TetrisEngine::DEFAULT_PLAYFIELD.y * 10 + 10,0);

    while (window.isOpen())
    {
        sf::Event event;

        scoreTxt.setString(toString(pf.GetScore()));

        if (cl.getElapsedTime().asSeconds() > 0.25) {
            if(pf.IsRunning)
                pf.HandleEvent(sf::Keyboard::Down);
            cl.restart();
        }
        else {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed)
                    if(pf.IsRunning)
                        pf.HandleEvent(event.key.code);
            }
        }

        window.clear();
        if (pf.IsRunning) {
            pf.Update();
            
        }
        window.draw(pf);
        window.draw(scoreTxt);
        window.display();
    }

    return 0;
}