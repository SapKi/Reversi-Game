//
// Created by or on 27/12/17.
//
#include <vector>
#include <iostream>
#include "GameControlling.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include "Command.h"


void Command::writeToClientMessage(string messageClient, int clientSocket) {
    int stringLength = messageClient.length();
    int n;
    //writing to the client message first write the size of the string and then the string
    n = (int)write(clientSocket, &stringLength, sizeof(int));
    if (n == -1) {
        cout << "Failed writing string length" << endl;
        exit(-1);
    }
    for(int i = 0; i < stringLength; i++) {
        n = (int) write(clientSocket, &messageClient[i], sizeof(char));
        if (n == -1) {
            cout << "Failed writing meaasge" << endl;
            exit(-1);
        }
    }
}

