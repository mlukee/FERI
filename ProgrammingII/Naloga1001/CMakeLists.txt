cmake_minimum_required(VERSION 3.21)
project(Naloga1001)

set(CMAKE_CXX_STANDARD 17)

add_executable(Naloga1001 naloga1001.cpp Artwork.cpp Artwork.h Artist.cpp Artist.h Date.cpp Date.h Gallery.cpp Gallery.h Painting.cpp Painting.h Sculpture.cpp Sculpture.h PrintIfPainting.cpp PrintIfPainting.h)
