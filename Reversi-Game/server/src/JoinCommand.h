//
// Created by sapir on 31/12/17.
//

#ifndef SERVER_JOINCOMMAND_H
#define SERVER_JOINCOMMAND_H
#include "Command.h"


class JoinCommand : public Command{
public:
    void execute(vector<string> args, int client);
};


#endif //SERVER_JOINCOMMAND_H
