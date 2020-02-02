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

int TetrisEngine::Playfield::ClearLines()
{
    int ClearedLines = 0;

    for (int y = 0; y < GetSize().y; y++) {
        bool GotAnEmpty = false;
        for (int x = 0; x < GetSize().x; x++) {
            auto obj = GetObjectAt(sf::Vector2i(x, y));
            if (obj == TetriminosColors::Blank || obj == TetriminosColors::Empty) {
                GotAnEmpty = true;
            }
        }

        if (GotAnEmpty == false) {
            for (int x = 0; x < GetSize().x; x++)
                SetObjectAt(TetriminosColors::Empty, sf::Vector2i(x, y));
            
            ShiftDownFromAbove(y - 1);
            ClearedLines++;
        }
           



    }

    return ClearedLines;
}

void Playfield::CleanMovingBeforeEvent(){
    Tetrimino& Moving = Tetriminos.back();
    UpdateGridForMovingTetrimino(Moving,TetriminosColors::Empty);
}

void Playfield::HandleEvent(sf::Keyboard::Key keyCode){
    if(Tetriminos.back().GetFallingState() == false){
        Score += 4;
        switch (ClearLines()) {
            case 1:
                Score += 40 * (Level + 1);
                break;
            case 2:
                Score += 100 * (Level + 1);
                break;
            case 3:
                Score += 300 * (Level + 1);
                break;
            case 4:
                Score += 1200 * (Level + 1);
                break;
            default:
                break;
        }
        AddTetrimino(Tetrimino::GetRandom());
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

    //if(!CheckFuturMoveWithOthers(mov))
    //    return false;

    if(FuturePos.x + (int)(width - ttr.GetDynamicBound(Bound::Left)) >= 0)
        if(FuturePos.x + (int)(ttr.GetDynamicBound(Bound::Right)) <= DEFAULT_PLAYFIELD.x)
            if (FuturePos.y + (int)(ttr.GetDynamicBound(Bound::Bottom)) <= DEFAULT_PLAYFIELD.y) {
                if (CheckFuturMoveWithOthers(mov)) {
                    return true;
                }
                else {
                    if(mov.y != 0)
                        Tetriminos.back().SetFallingState(false);
                    
                    return false;
                    
                }
            }
            else {
                Tetriminos.back().SetFallingState(false);
            }
                
        
    return false;
}

bool Playfield::CheckRotation(){
    Tetrimino ttr = Tetriminos.back();
    ttr.Rotate();
    auto width = ToUnderlying<TetriminosWidth>(ttr.GetWidth());
    auto FuturePos = ttr.GetPosition();

    if (FuturePos.x + (int)(width - ttr.GetDynamicBound(Bound::Left)) >= 0)
        if (FuturePos.x + (int)(ttr.GetDynamicBound(Bound::Right)) <= DEFAULT_PLAYFIELD.x)
            if (FuturePos.y + (int)(ttr.GetDynamicBound(Bound::Bottom)) <= DEFAULT_PLAYFIELD.y)
                if (CheckFuturRotateWithOthers())
                    return true;
                else
                    return false;
            else
                Tetriminos.back().SetFallingState(false);
            
        
    return false;
}

bool Playfield::CheckFuturMoveWithOthers(sf::Vector2i futureMov){

    Tetrimino ttr = Tetriminos.back();
    Tetrimino ttrBefore = ttr;
    ttr.Move(futureMov);
    auto pos = ttr.GetPosition();

    return ttr.IterateActiveCell([&](sf::Vector2i relPos) {
            sf::Vector2i gridPos(relPos.x + pos.x, relPos.y + pos.y);
            
            auto obj = GetObjectAt(gridPos);
            if (obj != TetriminosColors::Empty && obj != TetriminosColors::Blank) {
                return false;
            }
            
            return true;
        });
}

bool Playfield::CheckFuturRotateWithOthers() {

    Tetrimino ttr = Tetriminos.back();
    Tetrimino ttrBefore = ttr;
    ttr.Rotate();
    auto pos = ttr.GetPosition();

    return ttr.IterateActiveCell([&](sf::Vector2i relPos) {
            sf::Vector2i gridPos(relPos.x + pos.x, relPos.y + pos.y);

            auto obj = GetObjectAt(gridPos);
            if (obj != TetriminosColors::Empty && obj != TetriminosColors::Blank) {
                return false;
            }

            return true;
        });
}



void Playfield::Update(){
    Tetrimino& Moving = Tetriminos.back();
    UpdateGridForMovingTetrimino(Moving,Moving.GetColor());
}

int TetrisEngine::Playfield::GetScore()
{
    return Score;
}
