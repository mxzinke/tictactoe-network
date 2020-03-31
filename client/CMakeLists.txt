cmake_minimum_required(VERSION 3.12)
project(TicTacToe C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_C_FLAGS_RELEASE "-O3")

add_executable(TicTacToe
        main.c
        ttt_win_conditions.c
        level.c
        colours.c
        serverProtocol.c)

target_link_libraries(TicTacToe wsock32 ws2_32)