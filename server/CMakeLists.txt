cmake_minimum_required(VERSION 3.12)
project(TicTacToe C)

set(CMAKE_C_STANDARD 11)

add_executable(TicTacToe main.c serverProtocol.c)

target_link_libraries(TicTacToe wsock32 ws2_32)