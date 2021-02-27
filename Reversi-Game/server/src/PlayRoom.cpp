//
// Created by sapir on 28/12/17.
//

#include "PlayRoom.h"

PlayRoom::PlayRoom(int playerSocket, string &name) {
    p1 = playerSocket;
    p2 = 0;
    nameOfRoom = name;
    //the game didnt start yet
    this->started = 0;
}

string &PlayRoom::getRoomName()  {
    return this->nameOfRoom;
}

int PlayRoom::isRoomRunning() {
    return this->started;
}


void PlayRoom::setRoomName(const string &roomName) {
    this->nameOfRoom = roomName;
}

void PlayRoom::setSocket1(int socket1) {
    this->p1 = socket1;
}

void PlayRoom::startGame() {
    this->started = true;
}

void PlayRoom::setThread(pthread_t pthread1) {
    pthread = pthread1;
}

pthread_t PlayRoom::getThread() {
    return pthread;
}


void PlayRoom::connectPlayer2(int playerSocket) {
    this->p2 = playerSocket;
}

int PlayRoom::getOtherSocketNumber(int playerSocket) {
    if(playerSocket == p1)
        return p2;
    else if(playerSocket == p2) {
        return p1;
    }
    return 0;
}

int PlayRoom::getPlayerSocket1() {
    return p1;
}

int PlayRoom::getPlayerSocket2() {
    return p2;
}
