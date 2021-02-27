//
// Created by sapir on 28/12/17.
//

#ifndef EX1FINAL_PLAYROOM_H
#define EX1FINAL_PLAYROOM_H
#include <string>

using namespace std;


class PlayRoom {
public:
    PlayRoom(int playerSocket,string &name);
    int isRoomRunning();
    string &getRoomName();
    void setThread(pthread_t pthread);
    pthread_t getThread();
    void connectPlayer2(int playerSocket);
    int getOtherSocketNumber(int currPlayerSocket);
    void setRoomName(const string &roomName);
    void setSocket1(int socket1);
    void startGame();
    int getPlayerSocket1();
    int getPlayerSocket2();
private:
    string nameOfRoom;
    int p1;
    int p2;
    int started;
    pthread_t pthread;
};


#endif //EX1FINAL_PLAYROOM_H