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

int getNewInput(char *message) {
    char content[BUFFERSIZE];
    static int userID = -1;
    static int actuellUserID = 1;
    if (userID == -1) userID = getUserID();
    
    if (userID == actuellUserID) {
        char identifier, message[BUFFERSIZE] = {""};
        if (userID == 1) identifier = 'X';
        else identifier = 'O';
        printf("Spieler %c: ", identifier);
        if (fgets(message, sizeof(message), stdin) != NULL) {
            for (int i = 0; i < strlen(message); i++)
                if (message[i] == '\n' || message[i] == '\r') message[i] = '\0';
            sendData(message, userID);
        }
    } else {
        printf("Anderer Spieler spielt.\n");
    }

    if (recvData(content) > 0) {
        char *ptr;
        int i = 0, newActuellUserID;
        
        ptr = strtok(content, ";");
        while (ptr != NULL) {
            if (i == 0) strcpy(message, ptr);
            else if (i == 1) newActuellUserID = atoi(ptr);
            ptr = strtok(NULL, ";");
            i++;
        }
        if (strcmp(message, "NOGAME") != 0) {
            if (newActuellUserID == 1) actuellUserID++;
            else if (newActuellUserID == 2) actuellUserID = 1;
        } else {
            printf("Warte zuerst auf weitere Spieler!\n");
        }
        return newActuellUserID;
    } else {
        return 0;
    }

}

int getUserID() {
    return initilizeServerConnection();
}
int initilizeServerConnection() {
    static char serverAddress[24];
    char message[BUFFERSIZE];

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
            // recieving the welcome Message
            if (recvData(message) > 0) {
                if (strcmp(message, ("ECHO SpeedServer v" VERSION)) != 0) {
                    printf("\n# Please update your client! A newer Version is available.");
                    return -1;
                }
            } else {
                printf("Server shot off.\n");
            }

            if (sendData("WHICH", 0) >= 0) {
                char newUserID[BUFFERSIZE] = {""};
                if (recvData(newUserID) > 0) {
                    return atoi(&newUserID[7]);
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
    int returnValue;
    printf("TicTacToe-Server IP-Adresse: ");
    if (fgets(serverAddress, BUFFERSIZE, stdin) != NULL) returnValue = 1;
    else returnValue = 0;
    printf("\n\n");
    return returnValue;
}
int recvData(char *content) {
    int recvSize;

    if((recvSize = recv(s, content, BUFFERSIZE, 0)) == SOCKET_ERROR) {
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