cmake_minimum_required(VERSION 3.8)
project(cellautomata)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CellAutomaton.cc CellAutomaton.h RLEParser.cc RLEParser.h LifeLikeRule.cc LifeLikeRule.h Grid.h WrappingGrid.tcc WrappingGrid.h)
set(TEST_SOURCE_FILES test.cpp CellAutomaton.cc CellAutomaton.h RLEParser.cc RLEParser.h LifeLikeRule.cc LifeLikeRule.h Grid.h WrappingGrid.tcc WrappingGrid.h)

add_executable(cellautomata ${SOURCE_FILES})
add_executable(cellautomata_tests ${TEST_SOURCE_FILES})
