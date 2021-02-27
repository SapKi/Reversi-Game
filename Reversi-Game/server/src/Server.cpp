//
// Created by or on 04/12/17.
//


#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Server.h"
#include "CommandManager.h"
using namespace std;
#define MAX_CONNECTED_CLIENTS 10
#define MAX_COMMAND_LEN 20

Server::Server(int port): port(port), serverSocket(0), serverThread(0) {
    cout << "Server" << endl;
    running = true;
    cmd_manager_ = new CommandManager();
}

void Server::start() {
    // Create a socket point
    //at the lesson IPPROTO_TCP = 0
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == -1) {
        cout << "Error opening socket" << endl;
        exit(-1);
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        cout << "Error on binding" << endl;
        exit(-1);
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    //pthread_create(&serverThreadId, NULL, &acceptClients, (void *) serverSocket);

    pthread_t serverThread;
    pthread_create(&serverThread, NULL, Server::acceptLoopHelper, this);
}

// Handle requests from a specific client
void Server::handleTwoClients(string gameName, int client1, int client2) {
    char msgBuffer[200];
    int n;
    string msg;
    int currentPlayer = client1;
    int nextPlayer = client2;
    GameControlling *gc = GameControlling::getInstance();
    gc->eraseGame(gameName);

    while (true) {
        // Read  selected move from current player
        msg = receiveFrom(currentPlayer);
        if (msg == string()) {
            break;
        }

        // Write selected move to next player
        n = sendMes(nextPlayer, msg);
        if (n <= 0) {
            break;
        }

        // switch the turn to next player :D
        std::swap(currentPlayer, nextPlayer);
    }

    cout << "closing game " << gameName << endl;

    sendMes(currentPlayer, "play -1,-1");
    sendMes(nextPlayer, "play -1,-1");

    disconnectClient(currentPlayer);
    disconnectClient(nextPlayer);
}

/*
 * at first serverThreadId and serverSocket
 * were private then public and then required to be static
 */
void Server::stop() {
    running = false;
    closeServer();
}

void Server::closeServer() {
    GameControlling *instance = GameControlling::getInstance();
    running = 1;
    vector<pthread_t>::iterator iter = aliveThreads.begin();
    instance->closeAll();
    // close all threads
    while (iter!=aliveThreads.end()) {
        try {
            pthread_cancel(*iter);
        } catch (exception &e) {}
        iter++;
    }
    pthread_cancel(serverThread);
    shutdown(serverSocket, SHUT_RDWR);
    close(serverSocket);
}

void *Server::handleAcceptFirst(void *sc) {
    // client just connected
    // we expect one of those cmds ONLY: list_games, join, start
    // play, close cmds are invalid in this state
    SC *hy = (SC *) sc;
    int client_sock_id = hy->getClient();

    vector<string> args;
    string cmd = readCommand(hy->getClient(), &args);

    bool res = cmd_manager_->executeChosenCommand(cmd, args, client_sock_id);

    if (res) {
        cout << "exec cmd \"" << cmd << "\"" << endl;
    } else {
        cout << "ignoring cmd \"" << cmd << "\"" << ". only accepting cmds: start, join, list_games as first cmd after connection" << endl;
        disconnectClient(client_sock_id);
    }

    return NULL;
}

int Server::disconnectClient(int sock_id) {
    int res = -1;
    try{
        close(sock_id);
    } catch (exception &e){
        cout << "Error trying to close client socket " << sock_id << endl;
    }
    return res;
}
/*
void Server::setForSecPlayer(int clientSocket) {
    string input = "";
    string chosencommand;
    GameControlling* gc = GameControlling::getInstance();
    CommandManager *commandManager = new CommandManager(gc);//(gc)
    // in this method we get the user input and run the command by command manager

    vector<string> inputVec;
    input = readCommand(clientSocket, <#initializer#>);
    if (input != "list_games") {
        chosencommand = inputVec.at(0);
    } else {
        chosencommand = input;
        inputVec.push_back(input);
    }
    commandManager->executeChosenCommand(chosencommand, inputVec, clientSocket);
}
*/
string Server::readCommand(int clientSocket, vector<string> *args) {
    char commandStr[MAX_COMMAND_LEN];
    // Read the command from the socket

    int n = read(clientSocket, commandStr, MAX_COMMAND_LEN);
    if (n == -1) {
        cout << "Error reading command" << endl;
        return NULL;
    }
    cout << "Received command: " << commandStr << "from client id " << clientSocket << endl;

    string receivedMessage = Server::receiveFrom(clientSocket);

    // Split the command string to the command name and the arguments
    stringstream ss;
    ss << clientSocket;
    string clientSocketString = ss.str();
    istringstream iss(receivedMessage);
    string command;
    iss >> command;
    //Add client socket to args.
    args->push_back(clientSocketString);
    //Add all args to vector.
    while (iss) {
        string arg;
        iss >> arg;
        args->push_back(arg);
    }
    // Removing all spaces command
    command.erase(remove_if(command.begin(), command.end(), ::isspace), command.end());
    return command;
}

// todo: remove throw! add prints like in sendMes
string Server::receiveFrom(int clientSocket) {
    long n = -1;
    char message[200] = {0};

    try {
        // Read from socket.
        n = read(clientSocket, &message, sizeof(message));
        if (n > 0) {
            return string(message);
        }
        else if (n == -1) {
            cout << "Error trying to recv msg from client socket " << clientSocket << endl;
        } else if (n == 0) {
            //Checks if client disconnected and prints it.
            cout << "Client " << clientSocket << "found disconnected when trying to rcv msg" << endl;
        }
    } catch (exception &e){
        cout << "Exception trying to rcv msg from client socket " << clientSocket << endl;
    }
    return string();
}

int Server::sendMes(int clientSocket, string message) {
    char messageBuffer[200] = {0};
    strcpy(messageBuffer, message.c_str());
    int n = -1;

    try {
        //Read from socket.
        n = write(clientSocket, &messageBuffer, sizeof(messageBuffer));
        cout << "Sent client " << clientSocket << " msg: " << messageBuffer << endl;
    } catch (exception &e){
        cout << "Exception trying to send msg to client socket " << clientSocket << " msg: " << message << endl;
    }

    if (n == -1) {
        cout << "Error trying to send msg to client socket " << clientSocket << " msg: " << message << endl;
    } else if (n == 0) {
        //Checks if client disconnected and prints it.
        cout << "Client " << clientSocket << "found disconnected when trying to send msg: " << message << endl;
    }
    return n;
}

void* Server::handleAcceptFirstHelper(void* sc_v) {
    //void *context
    SC *sc = (SC*) sc_v;
    return sc->getServer()->handleAcceptFirst(sc);
}

void* Server::acceptLoopHelper(void *context) {
    //void *context
    ((Server *) context)->acceptLoop(context);
}

void *Server::acceptLoop(void *args) {
    while (running) {
        // new address to connect with the client
        sockaddr_in new_socket_addr;
        socklen_t new_socket_addr_size = sizeof(new_socket_addr);

        // Accept a new client connection
        int player = accept(serverSocket, (sockaddr *) &new_socket_addr, &new_socket_addr_size);
        if (player <= 0) {
            // err accepting client, do nothing
            continue;
        }

        SC *serverClientStructure = new SC(player, this);
        pthread_t currThread;
        pthread_create(&currThread, NULL, Server::handleAcceptFirstHelper, serverClientStructure);
        aliveThreads.push_back(currThread);
    }
}
