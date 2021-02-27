//
// Created by or on 27/12/17.
//

#ifndef EX1FINAL_COMMAND_H
#define EX1FINAL_COMMAND_H
#include <vector>
#include <iostream>
#include "GameControlling.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;


class Command {
public:
    virtual void execute(vector<string> args, int client) = 0;
    void writeToClientMessage(string messageClient, int clientSocket);
    // virtual ~Command() {}
};


#endif //EX1FINAL_COMMAND_H