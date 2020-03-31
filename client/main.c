#include "colours.h"
#include "ttt_win_conditions.h"
#include "level.h"
#include "serverProtocol.h"

int check_win_small_fields(char current_player) {
    int no_one_wins = 0;
    for (int pos_y = 0; pos_y < 3; pos_y++) {
        for (int pos_x = 0; pos_x < 3; pos_x++) {
            if (does_player_win_field(pos_y, pos_x, current_player)) {
                mark_field_won(pos_y, pos_x);
            }
            if (ult[pos_y][pos_x].successfull_rounds == 9) {
                no_one_wins++;
            }
            if (ult[pos_y][pos_x].won) {
                no_one_wins++;
            }
        }
    }
    return no_one_wins;
}

void play_ttt(void) {
    char current_player = 'X', coordinates[30] = {0}, player_colour[10] = {0};
    int currentUserID;

    print_field(0, current_player);
    set_colour_mode("red", player_colour);

    while ((currentUserID = getNewInput(coordinates, player_colour)) >= 0) {
        if (currentUserID == 1) {
            current_player = 'X';
        } else if (currentUserID == 2) {
            current_player = 'O';
        }

        if (current_player == 'O' && strcmp(coordinates, "NOGAME") != 0) {
            set_colour_mode("red", player_colour);
        } else if (strcmp(coordinates, "NOGAME") != 0) {
            set_colour_mode("green", player_colour);
        }

        if (strcmp(coordinates, "NOGAME") != 0 && set_coordinates(coordinates, current_player) == 0) {
            int no_one_wins = check_win_small_fields(current_player);

            if (does_player_win_ult(current_player) != -1) {
                print_field(1, current_player);
                printf("\n\t%sSpieler %c gewinnt!\033[0m\n", player_colour, current_player);
                break;
            } else if (no_one_wins == 9) {
                print_field(2, current_player);
                printf("\n\tUnentschieden!\033[0m\n");
                break;
            } else {
                print_field(0, current_player);
            }
        } else if (currentUserID >= 0) {
            print_field(0, current_player);
        }

        if (strcmp(coordinates, "NOGAME") == 0) {
            printf("\n\t%sWarte auf weitere Spieler...\n", player_colour);
        }

        for (int index = 0; index < sizeof(coordinates); index++)
            coordinates[index] = '\0';
    }

    printf("Server has been closed!");
}

void initialize_field() {
    for (int ult_y = 0; ult_y < 3; ult_y++) {
        for (int ult_x = 0; ult_x < 3; ult_x++) {
            for (int ttt_y = 0; ttt_y < 3; ttt_y++) {
                for (int ttt_x = 0; ttt_x < 3; ttt_x++) {
                    ult[ult_y][ult_x].ttt[ttt_y][ttt_x] = ' ';
                    ult[ult_y][ult_x].won = false;
                    ult[ult_y][ult_x].player = ' ';
                    ult[ult_y][ult_x].successfull_rounds = 0;
                }
            }
        }
    }
    strcpy(last_coordinate, "00");
}

int main() {
    initialize_field();
    play_ttt();

    return 0;
}