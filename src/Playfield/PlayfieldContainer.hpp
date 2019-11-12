#ifndef __PLAYFIELDCONTAINER__H__INCLUDED__
#define __PLAYFIELDCONTAINER__H__INCLUDED__

#pragma once

#include "./../Primitives/Grid.hpp"
#include "./../Tetrimino/Types.hpp"
#include "SFML/Graphics.hpp"

namespace TetrisEngine{

    const auto DEFAULT_PLAYFIELD = sf::Vector2i(10,24);

    template<typename T>
    bool IsInBound(const sf::Vector2<T> input,const sf::Vector2<T> target){
        if(input.x >= target.x || input.y >= target.y)
            return false;

        if(input.x < 0|| input.y < 0)
            return false;

        return true;
    }


    class PlayfieldContainer : public Grid{
        public:
            PlayfieldContainer(int);
            PlayfieldContainer(sf::Vector2i,int);
            TetriminosColors GetObjectAt(sf::Vector2i);
            int SetObjectAt(TetriminosColors,sf::Vector2i);
        private:
    };
}

#endif