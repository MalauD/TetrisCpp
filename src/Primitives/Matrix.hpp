#ifndef __MAT_H_INCLUDED__
#define __MAT_H_INCLUDED__

#include "stdint.h"
#include <algorithm>
#include "iostream"

namespace TetrisEngine {

    enum Rotation{
        CW90 = 3,
        CCW90 = 1
    };

    template<typename T,uint8_t Size>
    class Matrix{
        public:
            Matrix(const T (*array)[Size][Size]);
            virtual void Rotate(Rotation);
            virtual void Rotate(Rotation,uint8_t CustomSize);
            void Print();
        protected:
            T Arrays[Size][Size];
    };
}

#endif