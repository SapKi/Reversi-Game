//
// Created by sapir on 31/12/17.
//

#include "JoinCommand.h"
#include "Server.h"

void JoinCommand::execute(vector<string> args, int client) {
    GameControlling* gc = GameControlling::getInstance();
    if (gc->joinToGame(args[0], client)) {
        int client1_sock = gc->FindGameInList(args[0])->getPlayerSocket1();
        // client_sock_id - is the joining socket so he is the 2nd player
        Server::handleTwoClients(args[0], client1_sock, client);
    } else {
        Server::sendMes(client, "-1");
        Server::disconnectClient(client);
    }
}
