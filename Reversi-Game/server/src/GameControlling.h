//
// Created by sapir on 07/01/18.
//

#ifndef SERVER_GAMECONTROLLING_H
#define SERVER_GAMECONTROLLING_H
#include <vector>
#include "PlayRoom.h"


class GameControlling {
 private:
  static bool singletonFlag;
  vector<PlayRoom> listOfGames;
  void swapClients(int p1, int p2);
  int createMessage(int sender, int receiver);
  static pthread_mutex_t lock1;
  static pthread_mutex_t lock2;
  static pthread_mutex_t lock3;
  static pthread_mutex_t lock4;
  static pthread_mutex_t lock5;
  static GameControlling *gameControllingInstance;
  pthread_mutex_t mutexCommand;
  GameControlling();
 public:
  static GameControlling *getInstance();
  static void *threadclientclientHandler(void *pp);
  void *threadclientclient(void *args);
  struct CC {
   private:
    int client1;
    int client2;
   public:
    CC(int c1, int c2) : client1(c1), client2(c2) {}
    int getClient1() {
      return client1;
    }
    int getClient2() {
      return client2;
    }
  };
  struct PP {
    CC *args;
    GameControlling *inst;
  };
  PlayRoom *FindGameInList(string name);
  void eraseGame(string name);
  bool addGameToList(int clientSocket, string gameName);
  int JoinApproval(string name);
  //to change
  int isExsitInList(string name);
  void initialize(int playerSocket, int playerNum);
  string GetGamesList();
  bool joinToGame(string gameName, int clientSocket2);
  vector<PlayRoom>::iterator getGameIterator(string gameName);
  void closeAll();

};


#endif //SERVER_GAMECONTROLLING_H
