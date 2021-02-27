//
// Created by sapir on 30/12/17.
//
#include <vector>
#include <string>
#include "GameControlling.h"
#include "StartCommand.h"
#include "Server.h"

using namespace std;


//need to go to the client and to care to change the reading appropriately
void startCommand::execute(vector<string> args, int client) {
    //playroom name in listOfGames [1]
    GameControlling* gc = GameControlling::getInstance();
    if (gc->addGameToList(client, args[0])) {
        Server::sendMes(client, "1");
    } else {
        Server::sendMes(client, "-1");
        Server::disconnectClient(client);
    }
}