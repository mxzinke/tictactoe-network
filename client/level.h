#ifndef TICTACTOE_LEVEL_H
#define TICTACTOE_LEVEL_H

#endif //TICTACTOE_LEVEL_H

//region pragma once
#pragma once
#include <stdbool.h>
#pragma once
#include <stdlib.h>
#pragma once
#include <stdio.h>
#pragma once
#include <ctype.h>
#pragma once
#include <string.h>
//endregion

char last_coordinate[30];

struct ultimate {
    char ttt[3][3];
    bool won;
    char player;
    int successfull_rounds;
} ult[3][3];

void mark_field_won(int pos_y, int pos_x);

int set_coordinates(char *coordinate, char player);

char change_player(char current_player);

bool is_field_valid(int ult_x, int ult_y);

bool is_coordinate_occupied(char *coordinate);

char get_content_of_coordinate(char *coordinate);

bool get_position_in_field(char *coordinate, int *ult_x, int *ult_y, int *ttt_x, int *ttt_y);