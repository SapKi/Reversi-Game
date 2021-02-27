//
// Created by sapir on 14/11/17.
//

#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstring>
#define MAXLINE 10

using namespace std;
Player::Player(Board  * board, GameLogic * logic, int** validMoves , Board::State playerChar,
               int typeOfGame, ConsolePrinting* con,const char *filename) {
    this->playerChar = playerChar;
    this->copyBoard = board;
    this->copyLogic = logic;
    this->moves = validMoves;
    this->typeOfGame = typeOfGame;
    this->con = con;

    if(typeOfGame == 3) {
      char portBuffer[MAXLINE];
      int serverPort1;
      char address[MAXLINE];
      string buffer;
      char ip[MAXLINE];
      ifstream settings;
      settings.open(filename);
      //const char * buffer2;
      if (!settings) {
        throw "Can't open file";
      }
      // todo: make this  work

        getline(settings, buffer);
        sscanf(buffer.c_str(), "%s : %s", ip, address);
        if (!strcmp(ip, "IP")) {
            this->serverIP = address;
        } else {
            settings.close();
            throw "cannot parse IP";
        }
        getline(settings, buffer);
        sscanf(buffer.c_str(), "%s : %d", portBuffer, &serverPort1);
        if (!strcmp(portBuffer, "Port")) {
            this->serverPort = serverPort1;
        } else {
            settings.close();
            throw "cannot parse Port";
        }

//      this->serverIP = "127.0.0.1";
//      this->serverPort = 8222;
      settings.close();
    }
}


Player::Player(const char* filename){

}
Player::Player(const char *serverIP, int serverPort){

}
Board::State Player::GetplayerType(){
    return this->playerChar;
}

void Player::setPlayertype(Board::State stat) {
    this->playerChar = stat;
}

Board* Player::GetBoard(){
    return this->copyBoard;
}

Board::State** Player::GetBoardMatrix() {
    return this->GetBoard()->GetMatrix();
}
MajorGameLogic* Player::getGameLogic() {
    return this->copyLogic;
}

int** Player::GetMoves(){
    return this->moves;
}

int Player::getClientSocket() {
    return this->clientSocket;
}

void Player::setClientSocket(int socket) {
    this->clientSocket = socket;
}
