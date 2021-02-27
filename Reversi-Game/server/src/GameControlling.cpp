//
// Created by or on 27/12/17.
//

#include "GameControlling.h"
#include "ListCommand.h"
#include "Cell.h"
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>

bool GameControlling::singletonFlag = false;
GameControlling *GameControlling::gameControllingInstance = NULL;

GameControlling* GameControlling::getInstance() {
  if (!singletonFlag) {
    gameControllingInstance = new GameControlling();
  }
  return gameControllingInstance;
}

GameControlling::GameControlling() {
  singletonFlag = true;
  gameControllingInstance = new GameControlling();
  pthread_mutex_init(&mutexCommand, NULL);
}

//GameControlling *GameControlling::gameManager = 0;
pthread_mutex_t GameControlling::lock1;
pthread_mutex_t GameControlling::lock2;
pthread_mutex_t GameControlling::lock3;
pthread_mutex_t GameControlling::lock4;
pthread_mutex_t GameControlling::lock5;


bool GameControlling::addGameToList(int clientSocket, string gameName) {
  if (isExsitInList(gameName)!=1) {
    PlayRoom *gameRoom = new PlayRoom(clientSocket, gameName);
    pthread_mutex_lock(&mutexCommand);
    listOfGames.push_back(*gameRoom);
    pthread_mutex_unlock(&mutexCommand);
    initialize(clientSocket, 1);
    return true;
  } else {
    return false;
  }
}

/*
 * to add mutex and pthreads
 */
void GameControlling::eraseGame(string name) {
    //delete thread.
    //earse from game list
    // delete room (after new)
    PlayRoom* roomToDel = FindGameInList(name);
    if(isExsitInList(name) == 1) {
        //pthread_cancel(roomToDel->getThread());
        listOfGames.erase(getGameIterator(name));
    }
}

PlayRoom* GameControlling::FindGameInList(string name) {
    vector<PlayRoom>::iterator iter = listOfGames.begin();
    while (iter != listOfGames.end()) {
        if (name == iter->getRoomName()) {
            return &(*iter);
        }
    }

    return NULL;
}


int GameControlling::isExsitInList(string name) {
    //cout << name << endl;.

    if(!listOfGames.empty()) {
        vector<PlayRoom>::iterator iter = listOfGames.begin();
        while (iter != listOfGames.end()) {
            if (name == iter->getRoomName()) {
                //the game is in the list
                return 1;
            }
            iter++;
        }
    }
    return 0;
}

// todo: fix! return = bool. if false stop game, close sockets
void GameControlling::initialize(int clientSocket, int playerNum) {
    ssize_t flag = write(clientSocket, &playerNum, sizeof(playerNum));
    if (flag == -1) {
        cout << "Failed writing to socket" << endl;
        exit(1);
    }
}

int GameControlling::createMessage(int sender, int receiver) {
    Cell cell;
    try {
        ssize_t mess = read(sender, &cell, sizeof(cell));
        if (mess <= 0) {
            return 0;
        }
        mess = write(receiver, &cell, sizeof(cell));
        if (mess <= 0) {
            return 0;
        }
    } catch(exception e) {
        return 0;
    }
    return 1;
}


string GameControlling::GetGamesList() {
    string gamelist_tel;
    vector<PlayRoom>::iterator iter = listOfGames.begin();
    if (listOfGames.empty()) {
        return "\n";
    }
    while (iter != listOfGames.end()) {
      //if(!iter->isRoomRunning()) {
      gamelist_tel += iter->getRoomName() + "\n";
      //}
      iter++;
    }
    return gamelist_tel;
}

void GameControlling::closeAll() {
    int i;
    int size =(int) listOfGames.size();
    vector<PlayRoom>::iterator iter = listOfGames.begin();
    pthread_mutex_trylock(&mutexCommand);
    for(i = 0; i < size; i ++) {
        string name = iter->getRoomName();
        iter++;
        if(isExsitInList(name)) {
            eraseGame(name);
        }
    }
    pthread_mutex_unlock(&mutexCommand);

}

//my combined function that approving joinnig into  the game or not
int GameControlling::JoinApproval(string name){
    int check = 0;
    if(!listOfGames.empty()) {
        vector<PlayRoom>::iterator iter = listOfGames.begin();
        while (iter != listOfGames.end()) {
            if (name == iter->getRoomName()) {
                //checks if it is running
                if (FindGameInList(name)->isRoomRunning()) {
                    check = 1;
                }
                return check;
            }
            iter++;
        }
    }
    check = 0;
    return check;
}
vector<PlayRoom>::iterator GameControlling::getGameIterator(string gameName) {
    vector<PlayRoom>::iterator iter = listOfGames.begin();
    while (iter != listOfGames.end()) {
        if (gameName == iter->getRoomName()) {
            return iter;
        }
        iter++;
    }
    return iter;
}

bool GameControlling::joinToGame(string gameName, int clientSocket2) {
  PlayRoom *joining_room = FindGameInList(gameName);
  if (joining_room!=NULL) {
    pthread_mutex_lock(&mutexCommand);
    joining_room->connectPlayer2(clientSocket2);
    initialize(clientSocket2, 2);
    initialize(joining_room->getOtherSocketNumber(clientSocket2), 3);
    joining_room->startGame();
    pthread_mutex_unlock(&mutexCommand);

    this->swapClients(joining_room->getOtherSocketNumber(clientSocket2), clientSocket2);
    pthread_t currThread;
    CC *clientclient = new CC(joining_room->getOtherSocketNumber(clientSocket2), clientSocket2);
    PP *pp;
    pp->args = clientclient;
    pp->inst = this;
    pthread_create(&currThread, NULL, GameControlling::threadclientclientHandler, (void *) pp);

    pthread_mutex_lock(&mutexCommand);
    joining_room->setThread(currThread);
    pthread_mutex_unlock(&mutexCommand);
    return true;
    //connectionThreads.push_back(currThread);
  } else {
    return false;
  }
}

void GameControlling::swapClients(int p1, int p2) {
    int temp;
    int sender = p1;
    int receiver = p2;
    while (createMessage(sender, receiver)) {
        temp = sender;
        sender = receiver;
        receiver = temp;
    }
    close(p1);
    close(p2);
}

void* GameControlling::threadclientclientHandler(void* pp){
    GameControlling *inst = getInstance();
    inst->threadclientclient(((PP*)pp)->args);
}

void* GameControlling::threadclientclient(void *args) {
    CC ccInstance = * ((CC *) args);
    swapClients(ccInstance.getClient1(), ccInstance.getClient2());
    return NULL;
}

/*
void* GameControlling::threadclientclient(void *args) {
    CC ccInstance = * ((CC *) args);
    ((GameControlling*) ccInstance.getGCInstance())->swapClients(ccInstance.getClient1(), ccInstance.getClient2());
    return NULL;
}
 */