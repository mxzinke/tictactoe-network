#ifndef TICTACTOE_TTT_WIN_CONDITIONS_H
#define TICTACTOE_TTT_WIN_CONDITIONS_H

#endif //TICTACTOE_TTT_WIN_CONDITIONS_H

#pragma once
#include <stdbool.h>
#pragma once
#include "level.h"

bool check_row_ttt(int pos_y, int pos_x, char player);

bool check_column_ttt(int pos_y, int pos_x, char player);

bool check_diagonal_ttt(int pos_y, int pos_x, char player);

int check_row_ult(char player);

int check_column_ult(char player);

int check_diagonal_ult(char player);

int does_player_win_ult(char player);

bool does_player_win_field(int pos_y, int pos_x, char player);