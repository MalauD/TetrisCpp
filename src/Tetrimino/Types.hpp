#ifndef __TYPE_H_INCLUDED__
#define __TYPE_H_INCLUDED__

#pragma once

#include "./SFML/Graphics.hpp"
#include <type_traits>

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