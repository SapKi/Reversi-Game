cmake_minimum_required(VERSION 3.8)
project(src)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        AIPlayer.cpp
        AIPlayer.h
        Board.cpp
        Board.h
        Cell.cpp
        Cell.h
        ConsolePrinting.cpp
        ConsolePrinting.h
        Display.h
        FirstClient.cpp
        FirstClient.h
        Game.cpp
        Game.h
        GameLogic.cpp
        GameLogic.h
        GameLogicInterface.cpp
        GameLogicInterface.h
        HumanPlayer.cpp
        HumanPlayer.h
        main.cpp
        MajorGameLogic.cpp
        MajorGameLogic.h
        Player.cpp
        Player.h
        SecondClient.cpp
        SecondClient.h)

add_executable(src ${SOURCE_FILES})