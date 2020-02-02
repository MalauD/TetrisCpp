#include "PlayfieldContainer.hpp"


using namespace TetrisEngine;

PlayfieldContainer::PlayfieldContainer(int CellSize) : Grid(DEFAULT_PLAYFIELD,CellSize){
    
}

PlayfieldContainer::PlayfieldContainer(sf::Vector2i Size, int CellSize) : Grid(Size,CellSize){
    
}

TetriminosColors PlayfieldContainer::GetObjectAt(sf::Vector2i Pos) {
    sf::Vector2i size = Grid::GetSize();
    if(!IsInBound<int>(Pos,size))
        return TetriminosColors::Blank;

    return static_cast<TetriminosColors>(GridShape[Pos.x][Pos.y].getFillColor().toInteger());
}

int PlayfieldContainer::SetObjectAt(TetriminosColors tetriminos, sf::Vector2i Pos) {
    sf::Vector2i size = Grid::GetSize();
    if(!IsInBound<int>(Pos,size))
        return ToUnderlying<TetriminosColors>(TetriminosColors::Blank);

    sf::Color color(ToUnderlying<TetriminosColors>(tetriminos));
    GridShape[Pos.x][Pos.y].setFillColor(color);
}

void TetrisEngine::PlayfieldContainer::ShiftDownFromAbove(int line)
{
    for (int y = line; y >= 0; y--) {
        for (int x = 0; x < GetSize().x; x++) {
            auto curPos = sf::Vector2i(x, y);
            auto obj = GetObjectAt(curPos);
            SetObjectAt(obj, sf::Vector2i(curPos.x, curPos.y + 1));
            SetObjectAt(TetriminosColors::Empty, curPos);
        }
    }
}
