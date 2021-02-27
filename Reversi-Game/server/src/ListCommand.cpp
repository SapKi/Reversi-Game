//
// Created by sapir on 07/01/18.
//

#include "ListCommand.h"
#include "Server.h"

void ListCommand::execute(vector<string> args, int client) {
    //create list of room names and if it's not running put in vector to send
    Server::sendMes(client, GameControlling::getInstance()->GetGamesList());
    Server::disconnectClient(client);
}