//
// Created by sapir on 30/12/17.
//

#ifndef SERVER_STARTCOMMAND_H
#define SERVER_STARTCOMMAND_H
#include "Command.h"
#include "GameControlling.h"
#include <string>

#define STARTMESSAGE "Start"

class startCommand: public Command {
public:
    virtual void execute(vector<string> args, int client);
};


#endif //SERVER_STARTCOMMAND_H