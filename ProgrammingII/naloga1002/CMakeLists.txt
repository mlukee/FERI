cmake_minimum_required(VERSION 3.21)
project(naloga1002)

set(CMAKE_CXX_STANDARD 17)

add_executable(naloga1002 naloga1002.cpp Artist.h Artist.cpp Artwork.cpp Artwork.h Date.h Date.cpp Gallery.h Gallery.cpp Painting.cpp Painting.h PrintIfPainting.h PrintIfPainting.cpp Sculpture.h Sculpture.cpp)
