#include "Tetrimino.hpp"

using namespace TetrisEngine;

Tetrimino::Tetrimino(const TetriminosContainer& tc,const TetriminosColors Tcl) : MatrixU4(&tc), Color(Tcl){
    Position = STARTUP_POS_TETRIMINO;
    IsFalling = true;
}

Tetrimino::Tetrimino(const TetriminosContainer& tc,const TetriminosColors Tcl,sf::Vector2i pos) : MatrixU4(&tc), Color(Tcl){
    Position = pos;
    IsFalling = true;
}

sf::Vector2i Tetrimino::GetPosition(){
    return Position;
}

void Tetrimino::Move(sf::Vector2i mVec){
    Position += mVec;
}

void Tetrimino::Rotate(){
    MatrixU4::Rotate(Rotation::CCW90,ToUnderlying<TetriminosWidth>(GetWidth()));
}

bool Tetrimino::GetFallingState(){
    return IsFalling;
}

TetriminosColors Tetrimino::GetColor(){
    return Color;
}

void Tetrimino::SetFallingState(bool s){
    IsFalling = s;
}

bool Tetrimino::IsColoredAt(sf::Vector2i pos){
    if(Arrays[pos.x][pos.y] > 0){
        return true;
    }
    return false;
}

TetriminosWidth Tetrimino::GetWidth(){
    switch(GetColor()){
            case TetriminosColors::I:
                return TetriminosWidth::I_W;
            case TetriminosColors::O:
                return TetriminosWidth::O_W;
            case TetriminosColors::T:
                return TetriminosWidth::T_W;
            case TetriminosColors::L:
                return TetriminosWidth::L_W;
            case TetriminosColors::J:
                return TetriminosWidth::J_W;
            case TetriminosColors::Z:
                return TetriminosWidth::Z_W;
            case TetriminosColors::S:
                return TetriminosWidth::S_W;
            default:
                return TetriminosWidth::I_W;
        }
}

uint8_t Tetrimino::GetDynamicRightBound(){
    auto size = ToUnderlying<TetriminosWidth>(GetWidth());
    uint8_t counter[] = {0,0,0,0};


    for (int y = 0; y < size; y += 1) {
        bool GotA1 = false;
        for (int x = 0; x < size; x += 1) {
            if(Arrays[x][y] == 1 || GotA1 == false)
                counter[y]++;
            if(Arrays[x][y] == 1)
                GotA1 = true;
        }
    }
    auto LBound = *std::max_element(std::begin(counter),std::end(counter));
    return LBound;
}

uint8_t Tetrimino::GetDynamicLeftBound(){
    auto size = ToUnderlying<TetriminosWidth>(GetWidth());
    uint8_t counter[] = {0,0,0,0};


    for (int y = size - 1; y >= 0; y -= 1) {
        bool GotA1 = false;
        for (int x = size - 1; x >= 0; x -= 1) {
            if(Arrays[x][y] == 1 || GotA1 == false)
                counter[y]++;
            if(Arrays[x][y] == 1)
                GotA1 = true;
        }
    }
    auto LBound = *std::max_element(std::begin(counter),std::end(counter));
    return LBound;
}

uint8_t Tetrimino::GetDynamicBottomBound(){
    auto size = ToUnderlying<TetriminosWidth>(GetWidth());
    uint8_t counter[] = {0,0,0,0};


    for (int x = 0; x < size; x += 1) {
        bool GotA1 = false;
        for (int y = 0; y < size; y += 1) {
            if(Arrays[x][y] == 1 || GotA1 == false)
                counter[x]++;
            if(Arrays[x][y] == 1)
                GotA1 = true;
        }
    }
    auto LBound = *std::max_element(std::begin(counter),std::end(counter));
    return LBound;
}

uint8_t Tetrimino::GetDynamicTopBound(){
    auto size = ToUnderlying<TetriminosWidth>(GetWidth());
    uint8_t counter[] = {0,0,0,0};


    for (int x = size - 1; x >= 0; x -= 1) {
        bool GotA1 = false;
        for (int y = size - 1; y >= 0; y -= 1) {
            if(Arrays[x][y] == 1 || GotA1 == false)
                counter[x]++;
            if(Arrays[x][y] == 1)
                GotA1 = true;
        }
    }
    auto LBound = *std::max_element(std::begin(counter),std::end(counter));
    return LBound;
}

uint8_t Tetrimino::GetDynamicBound(Bound b){
    switch (b)
    {
    case Bound::Left:
        return GetDynamicLeftBound();
    case Bound::Right:
        return GetDynamicRightBound();
    case Bound::Top:
        return GetDynamicTopBound();
    case Bound::Bottom:
        return GetDynamicBottomBound();
    default:
        return -1;
    }
}