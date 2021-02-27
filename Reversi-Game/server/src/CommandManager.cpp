//
// Created by or on 27/12/17.
//
#include "Command.h"
#include "CommandManager.h"
#include "StartCommand.h"
#include "ListCommand.h"
#include "JoinCommand.h"
#include "GameControlling.h"


CommandManager::CommandManager() {
    //to add all the commands

    commandsMap["start"] = new startCommand();
    commandsMap["list_games"] = new ListCommand();
    commandsMap["join"] = new JoinCommand();
    /*commandsMap["Play"] = new PlayMoveC();
    commandsMap["close"] = new CloseSpecificGameC();*/

}

bool CommandManager::executeChosenCommand(string command, vector<string> arguments, int client) {
    if (commandsMap.find(command) == commandsMap.end()) {
        return false;
    }
    Command *commandObj = commandsMap[command];
    commandObj->execute(arguments, client);
    return true;
}
/*
CommandManager *CommandManager::getCommandManager() {
    if (commandManager == 0) {
        //Lock thread to prevent initialize twice
        pthread_mutex_lock(&lock);
        //first thread created commands manager -  second thread will not create another
        if (commandManager == 0) {
            //create new command manager
            commandManager = new CommandManager(gameControlling);
        }
        //unlock thread from commands manager.
        pthread_mutex_unlock(&lock);
    }
    return commandManager;
}*

void CommandManager::executeChosenCommand(string command, vector<string>& listOfGames, int clientnumber){
    Command *instanceCommand = commandsMap[command];
    vector<string> arguments = listOfGames;
    cout << "commandManager execute command:   " << command << endl;
    instanceCommand->execute(arguments, clientnumber, this->gameControlingInstance);
}*/