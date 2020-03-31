#include "level.h"


bool get_position_in_field(char *coordinate, int *ult_x, int *ult_y, int *ttt_x, int *ttt_y) {
    char y[5] = {};
    sprintf(y, "%c", coordinate[1]);
    int pos_y = strtol(y, NULL, 10);

    *ult_x = 0;
    *ult_y = 0;
    *ttt_x = 0;
    *ttt_y = 0;

    if (pos_y > 9) {
        return false;
    } else if (pos_y > 6) {
        *ult_y = 2;
        *ttt_y = pos_y - 7;
    } else if (pos_y > 3) {
        *ult_y = 1;
        *ttt_y = pos_y - 4;
    } else {
        *ult_y = 0;
        *ttt_y = pos_y - 1;
    }

    switch (toupper(coordinate[0])) {
        case 'A':
            *ult_x = 0;
            *ttt_x = 0;
            break;
        case 'B':
            *ult_x = 0;
            *ttt_x = 1;
            break;
        case 'C':
            *ult_x = 0;
            *ttt_x = 2;
            break;
        case 'D':
            *ult_x = 1;
            *ttt_x = 0;
            break;
        case 'E':
            *ult_x = 1;
            *ttt_x = 1;
            break;
        case 'F':
            *ult_x = 1;
            *ttt_x = 2;
            break;
        case 'G':
            *ult_x = 2;
            *ttt_x = 0;
            break;
        case 'H':
            *ult_x = 2;
            *ttt_x = 1;
            break;
        case 'I':
            *ult_x = 2;
            *ttt_x = 2;
            break;
        case '0':
            return true;
        default:
            return false;
    }
    return true;
}

char get_content_of_coordinate(char *coordinate) {
    int ult_x, ult_y, ttt_x, ttt_y;
    if (get_position_in_field(coordinate, &ult_x, &ult_y, &ttt_x, &ttt_y)) {
        char content = ult[ult_y][ult_x].ttt[ttt_y][ttt_x];
        return content;
    } else {
        return '0';
    }

}

bool is_coordinate_occupied(char *coordinate) {
    if (get_content_of_coordinate(coordinate) == ' ') {
        return false;
    } else {
        return true;
    }
}

bool is_field_valid(int ult_x, int ult_y) {
    int last_ult_x, last_ult_y, last_ttt_x, last_ttt_y;
    if (get_position_in_field(last_coordinate, &last_ult_x, &last_ult_y, &last_ttt_x, &last_ttt_y)) {

        if (strcmp(last_coordinate, "00") == 0) {
            return true;
        } else if (ult[ult_y][ult_x].won) {
            return false;
        } else if (ult[last_ttt_y][last_ttt_x].successfull_rounds == 9) {
            return true;
        } else if (last_ttt_x == ult_x && last_ttt_y == ult_y) {
            return true;
        } else if (ult[last_ttt_y][last_ttt_x].won) {
            return true;
        }
        return false;
    }
    return false;
}

int set_coordinates(char *coordinate, char player) {
    if (strlen(coordinate) == 2 && !is_coordinate_occupied(coordinate)) {
        int ult_x, ult_y, ttt_x, ttt_y;
        if (get_position_in_field(coordinate, &ult_x, &ult_y, &ttt_x, &ttt_y)) {
            if (is_field_valid(ult_x, ult_y) && !ult[ult_y][ult_x].won) {
                ult[ult_y][ult_x].ttt[ttt_y][ttt_x] = player;
                ult[ult_y][ult_x].successfull_rounds++;
                strcpy(last_coordinate, coordinate);
                return 0;
            } else return 1;
        } else return 1;
    } else return 1;
}

char change_player(char current_player) {
    if (current_player == 'X') return 'O';
    else return 'X';
}

void mark_field_won(int pos_y, int pos_x) {
    if (ult[pos_y][pos_x].player == 'X') {
        ult[pos_y][pos_x].ttt[0][0] = 'X';
        ult[pos_y][pos_x].ttt[0][1] = ' ';
        ult[pos_y][pos_x].ttt[0][2] = 'X';
        ult[pos_y][pos_x].ttt[1][0] = ' ';
        ult[pos_y][pos_x].ttt[1][1] = 'X';
        ult[pos_y][pos_x].ttt[1][2] = ' ';
        ult[pos_y][pos_x].ttt[2][0] = 'X';
        ult[pos_y][pos_x].ttt[2][1] = ' ';
        ult[pos_y][pos_x].ttt[2][2] = 'X';
    } else {
        ult[pos_y][pos_x].ttt[0][0] = ' ';
        ult[pos_y][pos_x].ttt[0][1] = 'O';
        ult[pos_y][pos_x].ttt[0][2] = ' ';
        ult[pos_y][pos_x].ttt[1][0] = 'O';
        ult[pos_y][pos_x].ttt[1][1] = ' ';
        ult[pos_y][pos_x].ttt[1][2] = 'O';
        ult[pos_y][pos_x].ttt[2][0] = ' ';
        ult[pos_y][pos_x].ttt[2][1] = 'O';
        ult[pos_y][pos_x].ttt[2][2] = ' ';
    }
    ult[pos_y][pos_x].won = true;
}