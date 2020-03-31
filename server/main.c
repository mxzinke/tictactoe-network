#include "serverProtocol.h"

int main() {
    int actualUserID;
    do {
        char cords[20] = {0}, identifier;
        actualUserID = getNewInput(cords);

        if (actualUserID == 1) identifier = 'X';
        else if (actualUserID == 2) identifier = 'O';
        printf("anderer Spieler: %s\n", cords);
    } while(actualUserID != 0);

    printf("Server shot off.\n");
    return 0;
}