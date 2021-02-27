#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#define MAXLINE 10
using namespace std;

#define PATH_TO_SETTINGS ("settings_server.txt")

int main() {
  int port;
  string buffer;
  char buf[MAXLINE];
  ifstream settings;
  settings.open(PATH_TO_SETTINGS);
  if (!settings) {
    cout << "Can't open config file" << endl;
    exit(-1);
  }
  getline(settings, buffer);
  sscanf(buffer.c_str(), "%s : %d", buf, &port);
  if (!strcmp(buf, "Port")) {
    //server1 = server2;
  } else {
    settings.close();
    cout << "cannot read valid port from config file" << endl;
    exit(-1);
  }

  Server server(port);
  try {
    server.start();
  } catch (const char *ex) {
    //cout << "Cannot start server. Reason: " << ex << endl;
    exit(-1);
  }

  // waiting for 'quit' command from user
  string inputstring = "";
  while (inputstring!="quit") {
    cout << "type ""quit"" and press ENTER to stop the server and all running games" << endl;
    cin >> inputstring;
  }
  server.stop();

  return 0;
};
