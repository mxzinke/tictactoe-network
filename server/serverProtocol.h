#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#define PORT 8080
#define BUFFERSIZE 1024
#define VERSION "1.0"

int getNewInput(char * inputVar); // returns the UserID of last recieved input, needs a input-variable for saving the input!
