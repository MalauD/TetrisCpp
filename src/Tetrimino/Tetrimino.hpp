#ifndef __TETRIMINO_H_INCLUDED__
#define __TETRIMINO_H_INCLUDED__

#pragma once

#include "Types.hpp"
#include "stdint.h"
#include "./../Primitives/Matrix.hpp"

namespace TetrisEngine{

    typedef Matrix<uint8_t,4> MatrixU4;
    typedef uint8_t TetriminosContainer[4][4];

    const sf::Vector2i STARTUP_POS_TETRIMINO = sf::Vector2i(5,0);

    const TetriminosContainer I = {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    };

    const TetriminosContainer O = {
        {1,1,0,0},
        {1,1,0,0},
        {0,0,0,0}
    };

    const TetriminosContainer T = {
        {1,1,1,0},
        {0,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };

    const TetriminosContainer L = {
        {1,1,1,0},
        {1,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }; 

    const TetriminosContainer J = {
        {1,1,1,0},
        {0,0,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }; 
    
    const TetriminosContainer Z = {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }; 

    const TetriminosContainer S = {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }; 

    enum class Bound{
        Left,
        Right,
        Bottom,
        Top
    };

    class Tetrimino : public MatrixU4{
        public:
            Tetrimino(const TetriminosContainer&,const TetriminosColors);
            Tetrimino(const TetriminosContainer&,const TetriminosColors,sf::Vector2i);
            sf::Vector2i GetPosition();
            bool GetFallingState();
            void SetFallingState(bool);
            bool IsColoredAt(sf::Vector2i);
            TetriminosColors GetColor();
            void Move(sf::Vector2i);
            void Rotate();
            TetriminosWidth GetWidth();
            uint8_t GetDynamicBound(Bound);
        private:
            const TetriminosColors Color;
            sf::Vector2i Position;
            bool IsFalling;
            uint8_t GetDynamicRightBound();
            uint8_t GetDynamicLeftBound();
            uint8_t GetDynamicBottomBound();
            uint8_t GetDynamicTopBound();
    };
}

#endif