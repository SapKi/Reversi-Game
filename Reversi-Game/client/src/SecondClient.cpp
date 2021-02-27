//
// Created by sapir on 10/12/17.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <limits>
#include <cstdlib>
#include <stdexcept>
#include <sstream>

#include "SecondClient.h"
SecondClient::SecondClient(Board* board, GameLogic* logic, int** validMoves, Board::State playerChar, int typeOfGame,ConsolePrinting* con,
                         const char* filename): Player(board,logic,validMoves,playerChar,typeOfGame,con,filename) {
    this->copyBoard = board;
    this->copyLogic = logic;
    this->moves = validMoves;
    this->typeOfGame = typeOfGame;
}

void SecondClient::connectToServer() {
    // Create a socket point
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == -1) {
        throw std::runtime_error("Error opening socket");
    }
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP.c_str(), &address)) {
        throw std::runtime_error("Can't parse IP address");
    }
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
    if (server == NULL) {
        throw std::runtime_error("Host is unreachable");
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *) &address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr, (char *) server->h_addr, server->h_length);
    // htons converts values between host and network byte orders
    serverAddress.sin_port = htons(serverPort);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
}

int SecondClient::getMoveFromServer() {
    ssize_t n;
    // Read the result from the server
    int res;
    n = read(clientSocket, &res, sizeof(res));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    return res;
}
void SecondClient::doTurn(int typeOfGame, Board *board, ConsolePrinting *con, Cell *&c) {
    int x,y;
    ssize_t n;
    char move_str[100];
    bool isThereMoves = copyLogic->validMoves(copyBoard->getBoard(), this->moves, this->GetplayerType());
    if (isThereMoves) {
        // move_str = *x**y* ints!!!!
        // x = 15, y = 3
        string move = move_str;
        n = read(clientSocket, move_str, sizeof(move_str));
        if (n==-1) {
            //error
        }

        stringstream ss(move_str);
        char comma;
        ss >> x;
        ss >> comma;
        ss >> y;

        //x = *((int *) move_str);
        //y = *((int *) (move_str + sizeof(unsigned int)));

        c = new Cell(x, y);
    } else {
        // read the no move  msg - do nothing with it
        n = read(clientSocket, move_str, sizeof(move_str));
        // set invalid cell values
        c = new Cell(-1, -1);
    }
}
void SecondClient::noMove(ConsolePrinting* con) {
    ssize_t n;
    con->noMorePosMove(this->GetplayerType());
    char no_move_str[50];
    n = read(clientSocket, no_move_str, sizeof(no_move_str));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    return;
}

void SecondClient::finishGame() {

}
