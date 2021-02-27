//
// Created by or on 04/12/17.
//

#ifndef UNTITLED2_SERVER_H
#define UNTITLED2_SERVER_H
#define NO_MOVES "NoMove"
#define END_GAME "End"

#include <pthread.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "CommandManager.h"
using namespace std;

enum ServerCmds {
  ServerCmdsStart = 0,
  ServerCmdsJoin,
  ServerCmdsListGames,
  ServerCmdsClose,
  ServerCmdsJoinPlay
};

class Server {

 public:
  Server(int port);
  void start();
  void stop();
  static void handleTwoClients(string gameName, int client1, int client2);

  //ServerCmds parseCmd(char *cmd_bytes, string *param);
  static int disconnectClient(int sock_id);
  static string receiveFrom(int clientSocket);
  static int sendMes(int clientSocket, string str);
  void *handleAcceptFirst(void *sc);
  void *acceptLoop(void *args);

  string readCommand(int clientSocket, vector<string> *args);
  struct SC {
   private:
    int clientnum;
    Server *server;
   public:
    SC(int client, Server *s) : clientnum(client), server(s) {}
    int getClient() {
      return clientnum;
    }
    Server *getServer() {
      return server;
    }
  };

 private:
  CommandManager *cmd_manager_;
  void closeServer();
  static void *handleAcceptFirstHelper(void *context);
  static void *acceptLoopHelper(void *context);
  int serverSocket;
  int port;
  bool running;
  pthread_t serverThread;
  vector<pthread_t> aliveThreads;

// the socket's file descriptor
};
#endif //UNTITLED2_SERVER_H
