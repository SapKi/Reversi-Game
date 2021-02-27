//
// Created by or on 27/12/17.
//

#ifndef EX1FINAL_COMMANDMANAGER_H
#define EX1FINAL_COMMANDMANAGER_H

#include <map>
#include "Command.h"
#include "GameControlling.h"



class CommandManager {
public:
    CommandManager();
    ~CommandManager();
    bool executeChosenCommand(string command, vector<string> args, int clientnumber);
    //static CommandManager *getCommandManager();
private:
    static pthread_mutex_t lock;
   // static CommandManager *commandManager;
    map<string, Command *> commandsMap;
};


#endif //EX1FINAL_COMMANDMANAGER_H