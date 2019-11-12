#include "Matrix.hpp"

using namespace TetrisEngine;

template<typename T,uint8_t Size>
Matrix<T,Size>::Matrix(const T (*array)[Size][Size]) {
    std::copy(array[0][0],array[0][0]+Size*Size,&Arrays[0][0]);
}

template<typename T,uint8_t Size>
void Matrix<T,Size>::Rotate(Rotation r) {
    for(int i = 0; i < r; i++){
        for (int x = 0; x < Size / 2; x += 1) {
            for (int y = x; y < Size - x - 1; y += 1) {
            
                int temp = Arrays[x][y]; 

                Arrays[x][y] = Arrays[y][Size-1-x]; 

                Arrays[y][Size-1-x] = Arrays[Size-1-x][Size-1-y]; 

                Arrays[Size-1-x][Size-1-y] = Arrays[Size-1-y][x]; 

                Arrays[Size-1-y][x] = temp; 
            }
        }
    }
}

template<typename T,uint8_t Size>
void Matrix<T,Size>::Rotate(Rotation r,uint8_t CustomSize) {
    for(int i = 0; i < r; i++){
        for (int x = 0; x < CustomSize / 2; x += 1) {
            for (int y = x; y < CustomSize - x - 1; y += 1) {
            
                int temp = Arrays[x][y]; 

                Arrays[x][y] = Arrays[y][CustomSize-1-x]; 

                Arrays[y][CustomSize-1-x] = Arrays[CustomSize-1-x][CustomSize-1-y]; 

                Arrays[CustomSize-1-x][CustomSize-1-y] = Arrays[CustomSize-1-y][x]; 

                Arrays[CustomSize-1-y][x] = temp; 
            }
        }
    }
}

template<typename T,uint8_t Size>
void Matrix<T,Size>::Print(){
    for (int i = 0; i < Size; i += 1) {
        for (int j = 0; j < Size; j += 1) {
            std::cout << Arrays[i][j] << " "; 
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template class Matrix<uint8_t,4>;