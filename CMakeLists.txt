cmake_minimum_required(VERSION 3.29)
project(Save_the_Word)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML
        GIT_TAG         2.6.1
)

FetchContent_MakeAvailable(SFML)


add_executable(Save_the_Word main.cpp
        Word.h
        Word.cpp
        Game.h
        Game.cpp
        MainMenu.h
        MainMenu.cpp
        Settings.h
        Settings.cpp
        Scoreboard.h
        Scoreboard.cpp
        Game.cpp
        Game.h
        MainMenu.cpp
        MainMenu.h
        Scoreboard.cpp
        Scoreboard.h
        Settings.cpp
        Settings.h
        Word.cpp
        Word.h)
target_link_libraries(Save_the_Word sfml-graphics)