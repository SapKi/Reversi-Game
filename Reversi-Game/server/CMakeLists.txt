cmake_minimum_required(VERSION 3.7)
project(server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/Server.cpp
        src/Server.h
src/Cell.h
src/Cell.cpp
src/Command.h
src/Command.cpp
src/CommandManager.h
src/CommandManager.cpp)

add_executable(untitled2 ${SOURCE_FILES})
