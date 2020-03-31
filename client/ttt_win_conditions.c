#include "ttt_win_conditions.h"

bool check_row_ttt(int pos_y, int pos_x, char player) {
    char first_field;
    char second_field;
    char third_field;

    for (int row = 0; row < 3; row++) {
        first_field = ult[pos_y][pos_x].ttt[row][0];
        second_field = ult[pos_y][pos_x].ttt[row][1];
        third_field = ult[pos_y][pos_x].ttt[row][2];
        if (first_field == player && second_field == player && third_field == player) {
            ult[pos_y][pos_x].won = true;
            ult[pos_y][pos_x].player = player;
            return true;
        }
    }
    return false;
}

bool check_column_ttt(int pos_y, int pos_x, char player) {
    char first_field;
    char second_field;
    char third_field;

    for (int column = 0; column < 3; column++) {
        first_field = ult[pos_y][pos_x].ttt[0][column];
        second_field = ult[pos_y][pos_x].ttt[1][column];
        third_field = ult[pos_y][pos_x].ttt[2][column];
        if (first_field == player && second_field == player && third_field == player) {
            ult[pos_y][pos_x].won = true;
            ult[pos_y][pos_x].player = player;
            return true;
        }
    }
    return false;
}

bool check_diagonal_ttt(int pos_y, int pos_x, char player) {
    char first_field;
    char second_field;
    char third_field;

    first_field = ult[pos_y][pos_x].ttt[0][0];
    second_field = ult[pos_y][pos_x].ttt[1][1];
    third_field = ult[pos_y][pos_x].ttt[2][2];
    if (first_field == player && second_field == player && third_field == player) {
        ult[pos_y][pos_x].won = true;
        ult[pos_y][pos_x].player = player;
        return true;
    }
    first_field = ult[pos_y][pos_x].ttt[2][0];
    second_field = ult[pos_y][pos_x].ttt[1][1];
    third_field = ult[pos_y][pos_x].ttt[0][2];
    if (first_field == player && second_field == player && third_field == player) {
        ult[pos_y][pos_x].won = true;
        ult[pos_y][pos_x].player = player;
        return true;
    }
    return false;
}

int check_row_ult(char player) {
    char first_field, second_field, third_field;
    for (int row = 0; row < 3; row++) {
        first_field = ult[row][0].player;
        second_field = ult[row][1].player;
        third_field = ult[row][2].player;
        if (first_field == player && second_field == player && third_field == player) {
            return row + 1;
        }
    }
    return -1;
}

int check_column_ult(char player) {
    char first_field, second_field, third_field;
    for (int column = 0; column < 3; column++) {
        first_field = ult[0][column].player;
        second_field = ult[1][column].player;
        third_field = ult[2][column].player;
        if (first_field == player && second_field == player && third_field == player) {
            return column + 1;
        }
    }
    return -1;
}

int check_diagonal_ult(char player) {
    char first_field, second_field, third_field;

    int diagonal = 0;
    first_field = ult[0][0].player;
    second_field = ult[1][1].player;
    third_field = ult[2][2].player;
    if (first_field == player && second_field == player && third_field == player) {
        diagonal += 1;
    }

    first_field = ult[0][2].player;
    second_field = ult[1][1].player;
    third_field = ult[2][0].player;
    if (first_field == player && second_field == player && third_field == player) {
        diagonal += 2;
    }
    if (diagonal == 0) return -1;
    return diagonal;
}

int does_player_win_ult(char player) {
    int result = 0;
    int buffer = check_row_ult(player);
    if (buffer != -1) {
        result = buffer * 100;
    }
    buffer = check_column_ult(player);
    if (buffer != -1) {
        result += buffer * 10;
    }
    buffer = check_diagonal_ult(player);
    if (buffer != -1) {
        result += buffer;
    }
    if (result == 0) return -1;
    return result;
}

bool does_player_win_field(int pos_y, int pos_x, char player) {
    if (check_row_ttt(pos_y, pos_x, player)) {
        return true;
    } else if (check_column_ttt(pos_y, pos_x, player)) {
        return true;
    } else if (check_diagonal_ttt(pos_y, pos_x, player)) {
        return true;
    }
    return false;
}