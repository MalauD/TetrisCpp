#include "SFML/Graphics.hpp"
#include "stdint.h"

#pragma once

namespace TetrisEngine {
    typedef std::unique_ptr<sf::RectangleShape[]> RectanglesArray;

    class Grid : public sf::Drawable{
        public:
            Grid(sf::Vector2i, int16_t cellsize);
            virtual sf::Vector2i GetSize();
        private:
            const int8_t Width;
            const int8_t Height;
            const int16_t CellSize;
            virtual void draw(sf::RenderTarget&,sf::RenderStates) const;
        protected:
            std::unique_ptr<RectanglesArray[]> GridShape;
    };
}

