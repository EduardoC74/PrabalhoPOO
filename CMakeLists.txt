cmake_minimum_required(VERSION 3.20)
project(TP)

set(CMAKE_CXX_STANDARD 14)

add_executable(TP main.cpp interface.cpp interface.h Ilha.cpp Ilha.h Zonas.cpp Zonas.h Trabalhadores.cpp Trabalhadores.h Edificios.cpp Edificios.h Saves.cpp Saves.h)
