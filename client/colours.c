#include "colours.h"

void set_colour_mode(char *colour_mode, char *destination) {
    if (strcmp(colour_mode, "red") == 0) {
        strcpy(destination, "\033[31m");
    } else if (strcmp(colour_mode, "green") == 0) {
        strcpy(destination, "\033[32m");
    } else if (strcmp(colour_mode, "yellow") == 0) {
        strcpy(destination, "\033[33m");
    } else if (strcmp(colour_mode, "blue") == 0) {
        strcpy(destination, "\033[34m");
    } else if (strcmp(colour_mode, "purple") == 0) {
        strcpy(destination, "\033[35m");
    } else if (strcmp(colour_mode, "cyan") == 0) {
        strcpy(destination, "\033[36m");
    } else if (strcmp(colour_mode, "white") == 0) {
        strcpy(destination, "\033[37;22m");
    } else if (strcmp(colour_mode, "grey") == 0) {
        strcpy(destination, "\033[30;1m");
    } else if (strcmp(colour_mode, "black") == 0) {
        strcpy(destination, "\033[90m");
    }
}

void colour_field(char colours[3][3][10], int mode, char player,  char colour_abc[10],
        char colour_def[10], char colour_ghi[10], char colour_123[10], char colour_456[10], char colour_789[10]) {
    for (int pos_y = 0; pos_y < 3; pos_y++) {
        for (int pos_x = 0; pos_x < 3; pos_x++) {
            if (ult[pos_y][pos_x].won) {
                if (ult[pos_y][pos_x].player == 'X') {
                    set_colour_mode("red", colours[pos_y][pos_x]);
                } else if (ult[pos_y][pos_x].player == 'O') {
                    set_colour_mode("green", colours[pos_y][pos_x]);
                }
                // region won
                if (mode == 1) {
                    int result = does_player_win_ult(player);
                    int diagonal = (result % 10);
                    result /= 10;
                    int column = (result % 10);
                    int row = (result / 10);

                    if (row > 0) {
                        row--;
                        for (int i = 0; i < 3; i++) {
                            set_colour_mode("yellow", colours[row][i]);
                        }
                    }
                    if (column > 0) {
                        column--;
                        for (int i = 0; i < 3; i++) {
                            set_colour_mode("yellow", colours[i][column]);
                        }
                    }
                    if (diagonal > 0) {
                        set_colour_mode("yellow", colours[1][1]);
                        if (diagonal == 1) {
                            set_colour_mode("yellow", colours[0][0]);
                            set_colour_mode("yellow", colours[2][2]);
                        } else if (diagonal == 2) {
                            set_colour_mode("yellow", colours[0][2]);
                            set_colour_mode("yellow", colours[2][0]);
                        } else if (diagonal == 3) {
                            set_colour_mode("yellow", colours[0][0]);
                            set_colour_mode("yellow", colours[2][2]);
                            set_colour_mode("yellow", colours[0][2]);
                            set_colour_mode("yellow", colours[2][0]);
                        }
                    }
                }
                //endregion
            } else if (ult[pos_y][pos_x].successfull_rounds == 9) {
                set_colour_mode("grey", colours[pos_y][pos_x]);
            } else if (is_field_valid(pos_x, pos_y)) {
                if (mode == 0) {
                    set_colour_mode("cyan", colours[pos_y][pos_x]);
                    switch (pos_y) {
                        case 0: set_colour_mode("cyan", colour_123); break;
                        case 1: set_colour_mode("cyan", colour_456); break;
                        case 2: set_colour_mode("cyan", colour_789); break;
                        default: break;
                    }
                    switch (pos_x) {
                        case 0: set_colour_mode("cyan", colour_abc); break;
                        case 1: set_colour_mode("cyan", colour_def); break;
                        case 2: set_colour_mode("cyan", colour_ghi); break;
                        default: break;
                    }
                } else {
                    set_colour_mode("white", colours[pos_y][pos_x]);
                }
            } else {
                set_colour_mode("white", colours[pos_y][pos_x]);
            }
        }
    }
}

void print_field(int mode, char player) {
    char colours[3][3][10] = {};

    char colour_abc[10];
    char colour_def[10];
    char colour_ghi[10];
    char colour_123[10];
    char colour_456[10];
    char colour_789[10];

    set_colour_mode("white", colour_123);
    set_colour_mode("white", colour_456);
    set_colour_mode("white", colour_789);
    set_colour_mode("white", colour_abc);
    set_colour_mode("white", colour_def);
    set_colour_mode("white", colour_ghi);
    colour_field(colours, mode, player, colour_abc, colour_def, colour_ghi, colour_123, colour_456, colour_789);

    char colour_white[10];
    set_colour_mode("white", colour_white);
    printf("\033[H\033[2J");
    printf("\t %sA B C %sD E F %sG H I\n", colour_abc, colour_def, colour_ghi);
    printf("\t%s1%s%c|%c|%c%s#%s%c|%c|%c%s#%s%c|%c|%c\n", colour_123,
           colours[0][0], ult[0][0].ttt[0][0], ult[0][0].ttt[0][1], ult[0][0].ttt[0][2], colour_white,
           colours[0][1], ult[0][1].ttt[0][0], ult[0][1].ttt[0][1], ult[0][1].ttt[0][2], colour_white,
           colours[0][2], ult[0][2].ttt[0][0], ult[0][2].ttt[0][1], ult[0][2].ttt[0][2]);
    printf("\t %s-+-+-%s#%s-+-+-%s#%s-+-+-%s\n", colours[0][0], colour_white, colours[0][1], colour_white, colours[0][2], colour_white);
    printf("\t%s2%s%c|%c|%c%s#%s%c|%c|%c%s#%s%c|%c|%c\n", colour_123,
           colours[0][0], ult[0][0].ttt[1][0], ult[0][0].ttt[1][1], ult[0][0].ttt[1][2], colour_white,
           colours[0][1], ult[0][1].ttt[1][0], ult[0][1].ttt[1][1], ult[0][1].ttt[1][2], colour_white,
           colours[0][2], ult[0][2].ttt[1][0], ult[0][2].ttt[1][1], ult[0][2].ttt[1][2]);
    printf("\t %s-+-+-%s#%s-+-+-%s#%s-+-+-%s\n", colours[0][0], colour_white, colours[0][1], colour_white, colours[0][2], colour_white);
    printf("\t%s3%s%c|%c|%c%s#%s%c|%c|%c%s#%s%c|%c|%c\n", colour_123,
           colours[0][0], ult[0][0].ttt[2][0], ult[0][0].ttt[2][1], ult[0][0].ttt[2][2], colour_white,
           colours[0][1], ult[0][1].ttt[2][0], ult[0][1].ttt[2][1], ult[0][1].ttt[2][2], colour_white,
           colours[0][2], ult[0][2].ttt[2][0], ult[0][2].ttt[2][1], ult[0][2].ttt[2][2]);
    printf("\t%s #################\n", colour_white);
    printf("\t%s4%s%c|%c|%c%s#%s%c|%c|%c%s#%s%c|%c|%c\n", colour_456,
           colours[1][0], ult[1][0].ttt[0][0], ult[1][0].ttt[0][1], ult[1][0].ttt[0][2], colour_white,
           colours[1][1], ult[1][1].ttt[0][0], ult[1][1].ttt[0][1], ult[1][1].ttt[0][2], colour_white,
           colours[1][2], ult[1][2].ttt[0][0], ult[1][2].ttt[0][1], ult[1][2].ttt[0][2]);
    printf("\t %s-+-+-%s#%s-+-+-%s#%s-+-+-%s\n", colours[1][0], colour_white, colours[1][1], colour_white, colours[1][2], colour_white);
    printf("\t%s5%s%c|%c|%c%s#%s%c|%c|%c%s#%s%c|%c|%c\n", colour_456,
           colours[1][0], ult[1][0].ttt[1][0], ult[1][0].ttt[1][1], ult[1][0].ttt[1][2], colour_white,
           colours[1][1], ult[1][1].ttt[1][0], ult[1][1].ttt[1][1], ult[1][1].ttt[1][2], colour_white,
           colours[1][2], ult[1][2].ttt[1][0], ult[1][2].ttt[1][1], ult[1][2].ttt[1][2]);
    printf("\t %s-+-+-%s#%s-+-+-%s#%s-+-+-%s\n", colours[1][0], colour_white, colours[1][1], colour_white, colours[1][2], colour_white);
    printf("\t%s6%s%c|%c|%c%s#%s%c|%c|%c%s#%s%c|%c|%c\n", colour_456,
           colours[1][0], ult[1][0].ttt[2][0], ult[1][0].ttt[2][1], ult[1][0].ttt[2][2], colour_white,
           colours[1][1], ult[1][1].ttt[2][0], ult[1][1].ttt[2][1], ult[1][1].ttt[2][2], colour_white,
           colours[1][2], ult[1][2].ttt[2][0], ult[1][2].ttt[2][1], ult[1][2].ttt[2][2]);
    printf("\t%s #################\n", colour_white);
    printf("\t%s7%s%c|%c|%c%s#%s%c|%c|%c%s#%s%c|%c|%c\n", colour_789,
           colours[2][0], ult[2][0].ttt[0][0], ult[2][0].ttt[0][1], ult[2][0].ttt[0][2], colour_white,
           colours[2][1], ult[2][1].ttt[0][0], ult[2][1].ttt[0][1], ult[2][1].ttt[0][2], colour_white,
           colours[2][2], ult[2][2].ttt[0][0], ult[2][2].ttt[0][1], ult[2][2].ttt[0][2]);
    printf("\t %s-+-+-%s#%s-+-+-%s#%s-+-+-%s\n", colours[2][0], colour_white, colours[2][1], colour_white, colours[2][2], colour_white);
    printf("\t%s8%s%c|%c|%c%s#%s%c|%c|%c%s#%s%c|%c|%c\n", colour_789,
           colours[2][0], ult[2][0].ttt[1][0], ult[2][0].ttt[1][1], ult[2][0].ttt[1][2], colour_white,
           colours[2][1], ult[2][1].ttt[1][0], ult[2][1].ttt[1][1], ult[2][1].ttt[1][2], colour_white,
           colours[2][2], ult[2][2].ttt[1][0], ult[2][2].ttt[1][1], ult[2][2].ttt[1][2]);
    printf("\t %s-+-+-%s#%s-+-+-%s#%s-+-+-%s\n", colours[2][0], colour_white, colours[2][1], colour_white, colours[2][2], colour_white);
    printf("\t%s9%s%c|%c|%c%s#%s%c|%c|%c%s#%s%c|%c|%c%s\n", colour_789,
           colours[2][0], ult[2][0].ttt[2][0], ult[2][0].ttt[2][1], ult[2][0].ttt[2][2], colour_white,
           colours[2][1], ult[2][1].ttt[2][0], ult[2][1].ttt[2][1], ult[2][1].ttt[2][2], colour_white,
           colours[2][2], ult[2][2].ttt[2][0], ult[2][2].ttt[2][1], ult[2][2].ttt[2][2], colour_white);
}
