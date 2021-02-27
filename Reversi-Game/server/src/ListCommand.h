//
// Created by sapir on 31/12/17.
//

#ifndef SERVER_LISTOFGAMES_H
#define SERVER_LISTOFGAMES_H

#include <vector>
#include "Command.h"


class ListCommand: public Command {
public:
    void execute(vector<string> args, int client);
};


#endif //SERVER_LISTOFGAMES_H
