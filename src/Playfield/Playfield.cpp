#include "Playfield.hpp"

using namespace TetrisEngine;

Playfield::Playfield(int cellSize) : PlayfieldContainer(cellSize){
    
}

void Playfield::AddTetrimino(Tetrimino ttr) {
    Tetriminos.push_back(ttr);
    UpdateGridForMovingTetrimino(ttr,ttr.GetColor());
}

void Playfield::UpdateGridForMovingTetrimino(Tetrimino Moving,TetriminosColors clr){
    auto pos = Moving.GetPosition();
    for(int x = pos.x; x < pos.x + 4; x += 1){
        for(int y = pos.y; y < pos.y + 4; y += 1){
            if(Moving.IsColoredAt(sf::Vector2i(x - pos.x, y - pos.y))){
                SetObjectAt(clr,sf::Vector2i(x,y));
            }
        }
    }
}

void Playfield::CleanMovingBeforeEvent(){
    Tetrimino& Moving = Tetriminos.back();
    UpdateGridForMovingTetrimino(Moving,TetriminosColors::Empty);
}

void Playfield::HandleEvent(sf::Keyboard::Key keyCode){
    if(Tetriminos.back().GetFallingState() == false){
        AddTetrimino(Tetrimino(S,TetriminosColors::S));
    }
        

    CleanMovingBeforeEvent();
    switch (keyCode)
    {
        case sf::Keyboard::Left:
            if(CheckMove(sf::Vector2i(-1,0)))
                Tetriminos.back().Move(sf::Vector2i(-1,0));
            break;
        case sf::Keyboard::Right:
            if(CheckMove(sf::Vector2i(1,0)))
                Tetriminos.back().Move(sf::Vector2i(1,0));
            break;
        case sf::Keyboard::Down:
            if(CheckMove(sf::Vector2i(0,1)))
                Tetriminos.back().Move(sf::Vector2i(0,1));
            break;
        case sf::Keyboard::R:
            if(CheckRotation())
                Tetriminos.back().Rotate();
            break;
        default:
            break;
    }
}

bool Playfield::CheckMove(sf::Vector2i mov){
    Tetrimino ttr = Tetriminos.back();
    ttr.Move(mov);
    auto width = ToUnderlying<TetriminosWidth>(ttr.GetWidth());
    auto FuturePos = ttr.GetPosition();

    if(!CheckFuturMoveWithOthers(mov))
        return false;

    if(FuturePos.x + (int)(width - ttr.GetDynamicBound(Bound::Left)) >= 0)
        if(FuturePos.x + (int)(ttr.GetDynamicBound(Bound::Right)) <= DEFAULT_PLAYFIELD.x)
            if(FuturePos.y +(int)(ttr.GetDynamicBound(Bound::Bottom)) <= DEFAULT_PLAYFIELD.y)
                return true;
            else
                Tetriminos.back().SetFallingState(false);
            
        
    return false;
}

bool Playfield::CheckRotation(){
    Tetrimino ttr = Tetriminos.back();
    ttr.Rotate();
    auto width = ToUnderlying<TetriminosWidth>(ttr.GetWidth());
    auto FuturePos = ttr.GetPosition();

    if(FuturePos.x + (int)(width - ttr.GetDynamicBound(Bound::Left)) >= 0)
        if(FuturePos.x + (int)(ttr.GetDynamicBound(Bound::Right)) <= DEFAULT_PLAYFIELD.x)
            if(FuturePos.y +(int)(ttr.GetDynamicBound(Bound::Bottom)) <= DEFAULT_PLAYFIELD.y)
                return true;
            else
                Tetriminos.back().SetFallingState(false);
            
        
    return false;
}

bool Playfield::CheckFuturMoveWithOthers(sf::Vector2i futureMov){ //? May work... In reality NOOOO

    Tetrimino ttr = Tetriminos.back();
    Tetrimino ttrBefore = ttr;
    ttr.Move(futureMov);
    auto pos = ttr.GetPosition();
    for(int x = pos.x; x < pos.x + 4; x += 1){
        for(int y = pos.y; y < pos.y + 4; y += 1){
            sf::Vector2i Temp = sf::Vector2i(x - pos.x, y - pos.y);
            if(ttr.IsColoredAt(Temp) || true){
                if(ttrBefore.IsColoredAt(Temp)){
                    //ne pas faire confiance à Plafield::GetColorAt
                    //! Donc pas de pb pour cette piece

                }else{
                    if(GetObjectAt(sf::Vector2i(x,y)) != TetriminosColors::Empty){
                        return false;
                    }
                }
            }
        }
    }
    return true;
}



void Playfield::Update(){
    Tetrimino& Moving = Tetriminos.back();
    UpdateGridForMovingTetrimino(Moving,Moving.GetColor());
}