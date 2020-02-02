#ifndef __PLAYFIELD_H_INCLUDED__
#define __PLAYFIELD_H_INCLUDED__

#pragma once

#include "PlayfieldContainer.hpp"
#include "./../Tetrimino/Tetrimino.hpp"
#include "SFML/Graphics.hpp"

namespace TetrisEngine{
    class Playfield : public PlayfieldContainer{
        public:
            Playfield(int cellSize);
            void AddTetrimino(Tetrimino);
            void HandleEvent(sf::Keyboard::Key);
            void Update();
            int GetScore();
            int Level = 1;
        private:
            std::vector<Tetrimino> Tetriminos;
            int ClearLines();
            void CleanMovingBeforeEvent();
            void UpdateGridForMovingTetrimino(Tetrimino,TetriminosColors);
            bool CheckMove(sf::Vector2i);
            bool CheckFuturMoveWithOthers(sf::Vector2i);
            bool CheckFuturRotateWithOthers();
            bool CheckRotation();
            int Score = 0;
    };
}
#endif