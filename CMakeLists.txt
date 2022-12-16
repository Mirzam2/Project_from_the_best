cmake_minimum_required(VERSION 3.10)
project(Tutorial)
set(SOURCE_EXE main.cpp
Casino_realization.cpp
casino.h
Game_realization.cpp
Dice_realisation.cpp
Hostandplayers.cpp
Roulete_realisation.cpp
BlackJack.cpp
)	
add_executable(main ${SOURCE_EXE})