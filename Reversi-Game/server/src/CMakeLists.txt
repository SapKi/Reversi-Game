cmake_minimum_required(VERSION 3.7)
project(server)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        Cell.h
        Cell.cpp
        main.cpp
        Server.cpp
        Server.h CommandManager.cpp CommandManager.h PlayRoom.cpp PlayRoom.h StartCommand.cpp StartCommand.h ListCommand.cpp ListCommand.h JoinCommand.cpp JoinCommand.h Command.cpp Command.h GameControlling.cpp GameControlling.h)

add_executable(server ${SOURCE_FILES} main.cpp)