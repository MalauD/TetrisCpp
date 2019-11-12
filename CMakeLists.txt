# CMakeList.txt : projet CMake pour TetrisCpp, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)
project(TetrisCpp VERSION 0.1.0)

set(SFML_DIR "C:/Users/malau/Downloads/SFML-2.5.1-windows-gcc-5.1.0-tdm-32-bit/SFML-2.5.1/lib/cmake/SFML")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

# Ajoutez une source à l'exécutable de ce projet.
file(GLOB_RECURSE SRCs "./src/*")
file(GLOB_RECURSE TestsFiles "./test/*")

set(TestFramework "./lib/catch.hpp")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (App ${SRCs})
add_executable (Tests ${SRCs} ${TestsFiles} ${TestFramework})
target_link_libraries(App sfml-graphics sfml-audio)
target_link_libraries(Tests sfml-graphics sfml-audio)