// serverProtocol - Content
// !!! PLEASE DON'T EDIT THESE DATA !!!
#include "serverProtocol.h"

WSADATA wsa;
SOCKET s;
struct sockaddr_in server;

int getUserID();
int initilizeServerConnection();

int getServerAddress(char *);
int recvData(char *);
int sendData(char *, int);

int getNewInput(char *content, char *player_colour) {
    char current_player = 0;
    static int actualUserID = 1;
    static int userID = -1;
    if (userID == -1) userID = getUserID();

    if (actualUserID == 1) current_player = 'X';
    else if (actualUserID == 2) current_player = 'O';

    if (userID == actualUserID) {
        char message[BUFFERSIZE] = {0};
        while (strlen(message) != 2) {
            printf("\n\t%sSpieler %c: \033[0m", player_colour, current_player);
            if (fgets(message, sizeof(message), stdin) != NULL) {
                for (int i = 0; i < strlen(message); i++)
                    if (message[i] == '\n' || message[i] == '\r') message[i] = '\0';
            }
        }
        if (sendData(message, userID) == SOCKET_ERROR) return -1;
    } else if (userID > 0) {
        printf("\n\t%sAnderer Spieler spielt gerade. Am Zug ist Spieler %c.\n", player_colour, current_player);
    } else if (userID == 0) {
        printf("\n\t%sDu bist nur Zuschauer. Am Zug ist Spieler %c.\n", player_colour, current_player);
    }

    if (userID >= 0 && recvData(content) > 0) {
        char *ptr;
        int i = 0, newActualUserID = 0;
        
        ptr = strtok(content, ";");
        while (ptr != NULL) {
            if (i == 0) strcpy(content, ptr);
            else if (i == 1) newActualUserID = strtol(ptr, NULL, 10);
            ptr = strtok(NULL, ";");
            i++;
        }
        if (strcmp(content, "NOGAME") != 0) {
            if (newActualUserID == 1) actualUserID++;
            else if (newActualUserID == 2) actualUserID = 1;
        }
        return newActualUserID;
    } else return -1;
}

int getUserID() {
    return initilizeServerConnection();
}
int initilizeServerConnection() {
    static char serverAddress[26] = {0};

    if (getServerAddress(serverAddress)) {
        if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
            int errorCode = WSAGetLastError();
            printf("Failed. Error Code: %d", errorCode);
            return -errorCode;
        }
        if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
            int errorCode = WSAGetLastError();
            printf("Could not create socket: %d", errorCode);
            return -errorCode;
        }

        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        server.sin_addr.s_addr = inet_addr(serverAddress);

        if (connect(s, (struct sockaddr *)&server, sizeof(server)) == 0) {
            char message[BUFFERSIZE] = {0};
            if (recvData(message) > 0) {
                if (strcmp(message, ("ECHO SpeedServer v" VERSION)) != 0) {
                    printf("\n# Please update your client! A newer Version is available.\n");
                    return -1;
                }
            } else {
                printf("Server shot off.\n");
            }

            if (sendData("WHICH", 0) >= 0) {
                char newUserID[BUFFERSIZE] = {""};
                if (recvData(newUserID) > 0) {
                    return (newUserID[7] - 48);
                } 
            }

        } else {
            int errorCode;
            if ((errorCode = WSAGetLastError()) == WSAEADDRNOTAVAIL) {
                printf("Address not Available.");
                return -errorCode;
            } else if (errorCode == WSAENETDOWN || errorCode == WSAENETUNREACH) {
                printf("Your Network is down.");
                return -errorCode;
            } else {
                printf("No connection possible, errorcode: %d %s", WSAGetLastError(), serverAddress);
                return -errorCode;
            }
        }
    } else return -1;
}

int getServerAddress(char *serverAddress) {
    printf("*** TicTacToe-Server IP-Adresse: ");
    if (fgets(serverAddress, BUFFERSIZE, stdin) != NULL) {
        for (int i = 0; i < strlen(serverAddress); i++)
            if (serverAddress[i] == '\n' || serverAddress[i] == '\r') serverAddress[i] = '\0';
        return 1;
    } else return 0;
}
int recvData(char *content) {
    int recvSize;

    if((recvSize = recv(s, content, BUFFERSIZE, 0)) == SOCKET_ERROR) {
        printf("Error: %i", WSAGetLastError());
        return -1;
    } else {
        content[recvSize] = '\0';
    }
    
    return recvSize;
}
int sendData(char *content, const int userID) {
    char message[BUFFERSIZE] = "";
    int returnValue;

    sprintf(message, "%s;%i", content, userID);

    returnValue = send(s, message, sizeof(message), 0);
    return returnValue;
}