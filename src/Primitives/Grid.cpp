#include "Grid.hpp"

using namespace TetrisEngine;

Grid::Grid(sf::Vector2i size,int16_t cellsize) : Width(size.x), Height(size.y), CellSize(cellsize){
    GridShape = std::unique_ptr<RectanglesArray[]>(new RectanglesArray[size.x]);
    for(size_t i = 0; i < size.x; ++i)
        GridShape[i] = RectanglesArray(new sf::RectangleShape[size.y]);
        
    for(size_t i = 0; i < Width; ++i){
        for(size_t j = 0; j < Height; ++j){
            GridShape[i][j].setSize(sf::Vector2f(CellSize,CellSize));
            GridShape[i][j].setOutlineColor(sf::Color::Blue);
            GridShape[i][j].setFillColor(sf::Color::Color::Black);
            GridShape[i][j].setOutlineThickness(1.0f);
            GridShape[i][j].setPosition(i*CellSize + 1.0f, j*CellSize + 1.0f);
        }
    }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0;i<Width;++i)
        for(int j=0;j<Height;++j)
            target.draw(GridShape[i][j]);
        
}

inline sf::Vector2i Grid::GetSize(){
    return sf::Vector2i(Width,Height);
}
