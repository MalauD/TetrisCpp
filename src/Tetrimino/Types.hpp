#ifndef __TYPE_H_INCLUDED__
#define __TYPE_H_INCLUDED__

#pragma once

#include "./SFML/Graphics.hpp"
#include <type_traits>
#include <random>

namespace TetrisEngine{

    template <typename E>
    constexpr inline auto ToUnderlying(E e) noexcept
    {
        return static_cast<std::underlying_type_t<E>>(e);
    }

    enum class TetriminosColors : unsigned int{ 
        Blank = 0xFFFFFFFF,
        Empty = 0x000000FF,
        I = 0x44FFFFFF,
        O = 0xFFFF44FF,
        T = 0xFF44FFFF,
        L = 0xFF8800FF,
        J = 0x0000F0FF,
        Z = 0xF00000FF,
        S = 0x00F000FF
    };

    struct TetriminosColorsRnd {
        static TetriminosColors Get() {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 6);

            switch (dist6(rng))
            {
            case 0:
                return TetriminosColors::I;
            case 1:
                return TetriminosColors::O;
            case 2:
                return TetriminosColors::T;
            case 3:
                return TetriminosColors::L;
            case 4:
                return TetriminosColors::J;
            case 5:
                return TetriminosColors::Z;
            case 6:
                return TetriminosColors::S;
            }
        }
    };

    enum class TetriminosWidth : unsigned int{
        I_W = 4,
        O_W = 2,
        T_W = 3,
        L_W = 3,
        J_W = 3,
        Z_W = 3,
        S_W = 3
    };
}

#endif