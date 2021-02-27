//Sapir Kikoz 207071192
#include <iostream>
#include <limits>
#include <vector>
#include <sstream>
#include "Game.h"
#include "Player.h"
#include "AIPlayer.h"
#include "HumanPlayer.h"
#include "ConsolePrinting.h"
#include "Display.h"
#include "FirstClient.h"
#include "SecondClient.h"
//#include "../server/PlayRoom.h"
// todo: remove
#define PATH_TO_SETTINGS "settings_client.txt"

using namespace std;
string ServerMenu(FirstClient *client_);
vector<string> ParseGame(string tel);
int GetSelection(int numOfOptions);
void PrintListOfGames(vector<string> listOfGames);
/*
 * The main function of the program - currently
 * creats a board and printing it to the screen.
 */
int main() {
  //the default size ofd the matrix
  int rows = 8, cols = 8;
  int check = 0;
  int typeOfGame;
  ConsolePrinting *con = new ConsolePrinting();
  con->chooseGameOptions();

  const char *filename = PATH_TO_SETTINGS;

  while (check==0) {
    cin >> typeOfGame;
    cout << endl;
    if (typeOfGame!=1 && typeOfGame!=2 && typeOfGame!=3) {
      con->noValidOption();
    } else check = 1;
  }

  Game *myGame = new Game(rows, cols, con, filename);

  if (typeOfGame==1) {
    //if 1 create AI player
    Player *UserPlayer = new HumanPlayer(myGame->GetBoard(),
                                         myGame->getGameLogic(),
                                         myGame->GetMoves(),
                                         Board::Black,
                                         typeOfGame,
                                         con,
                                         filename);
    Player *playerAI = new AIPlayer(myGame->GetBoard(),
                                    myGame->getGameLogic(),
                                    myGame->GetMoves(),
                                    Board::White,
                                    UserPlayer,
                                    typeOfGame,
                                    con,
                                    filename);
    myGame->gameFlow(UserPlayer, playerAI, typeOfGame, con);
  } else if (typeOfGame==2) {
    //if 2 create human player
    Player *UserPlayer1 = new HumanPlayer(myGame->GetBoard(),
                                          myGame->getGameLogic(),
                                          myGame->GetMoves(),
                                          Board::Black,
                                          typeOfGame,
                                          con,
                                          filename);
    Player *UserPlayer2 = new HumanPlayer(myGame->GetBoard(),
                                          myGame->getGameLogic(),
                                          myGame->GetMoves(),
                                          Board::White,
                                          typeOfGame,
                                          con,
                                          filename);
    myGame->gameFlow(UserPlayer1, UserPlayer2, typeOfGame, con);
  } else if (typeOfGame==3) {

FirstClient * temp = new FirstClient(myGame->GetBoard(),
                                           myGame->getGameLogic(),
                                           myGame->GetMoves(),
                                           Board::Black,
                                           typeOfGame,
                                           con,
                                           filename);
    Player *senderPlayer =temp;
    senderPlayer->setPlayertype(Board::Black);
    senderPlayer->connectToServer();
    string playerIndex = ServerMenu(temp);

    if (playerIndex=="1") {
      Player *reciverPlayer = new SecondClient(myGame->GetBoard(),
                                               myGame->getGameLogic(),
                                               myGame->GetMoves(),
                                               Board::White,
                                               typeOfGame,
                                               con,
                                               filename);
      reciverPlayer->setPlayertype(Board::White);
      // reciverPlayer->connectToServer();
      reciverPlayer->setClientSocket(senderPlayer->getClientSocket());
      myGame->gameFlow(senderPlayer, reciverPlayer, typeOfGame, con);

    } else if (playerIndex=="2") {
      con->connectedToServerMessage();
      senderPlayer->setPlayertype(Board::White);
      Player *reciverPlayer = new SecondClient(myGame->GetBoard(),
                                               myGame->getGameLogic(),
                                               myGame->GetMoves(),
                                               Board::Black,
                                               typeOfGame,
                                               con,
                                               filename);
      reciverPlayer->setPlayertype(Board::Black);
      // reciverPlayer->connectToServer();
      reciverPlayer->setClientSocket(senderPlayer->getClientSocket());
      myGame->gameFlow(reciverPlayer, senderPlayer, typeOfGame, con);
    }
    else {
      cout << "invalid index" << endl;
    }
  }
  return 0;
}

string ServerMenu(FirstClient *client_) {
  const int ret_code_len = 3;
  char game_name[200];
  string sym;
  while (1) {
    cout<<"1. start"<<endl;
    cout<<"2. join"<<endl;
    int select;
    while (1) {
      cin >> select;
      if (select!=1 && select!=2) {
        cout<<"invalid option, please enter your choice 1 or 2"<<endl;
      } else { break; }
    }
    // print menu:
    //            1) start
    //            2) join
    //  then get the index. if index != 1 || 2 print menu again

    // =========== join ============
    if (select==1) {
      printf("Enter game name to start: ");
      scanf(" %s", game_name);
      std::string cmd = "start " + std::string(game_name);
      client_->WriteToServer(cmd);

      string tel;
      int b = client_->ReadFromServer(tel);
      // != -1
      if (tel != "-1") {
        std::cout << "started game \"" << game_name << "\"" << std::endl;
        std::cout << "waiting for 2nd player to connect... " << std::endl; // residentSleeper
        // get symbol
        b = client_->ReadFromServer(sym);
        break;
      }
      std::cout << "failed to connect to game \"" << game_name << "\"" << std::endl;
    }
      // =========== start ============
    else if (select==2) {
      client_->WriteToServer("list_games");
      string game_list_tele;
      int b3 = client_->ReadFromServer(game_list_tele);
      std::vector<std::string> game_names = ParseGame(game_list_tele);
      // reconnect to server - connection closed by server after game_list cmd
      client_->connectToServer();
      if (game_names.size()==0) {
        std::cout << "there are no games to join" << std::endl;
        continue;
      }

      PrintListOfGames(game_names);
      select = GetSelection(game_names.size());
      std::string name = game_names[select - 1];
      std::string cmd = "join " + name;
      int b4 = client_->WriteToServer(cmd);
      // get err code (-1) OR symbol
      b4 = client_->ReadFromServer(sym);
      // != -1
      if (sym!="-1") {
        std::cout << "joined to game \"" << name << "\"" << std::endl;
        break;
      }
      std::cout << "failed to join game \"" << name << "\"" << std::endl;
    }
    // server disconnects us for every failed cmd
    client_->connectToServer();
  }



  return sym;
}

/*
 * get num of options and running while we get thge right index of the opption
 */
int GetSelection(int numOfOptions) {
  int check;
  int select;
  while (1) {
    cin >> select;
    cout << endl;
    if (select <= 0 || select > numOfOptions) {
      cout << "invalid option, please enter your choice number from the given options" << endl;
    } else {
      break;
    }
  }
  return select;

}


vector<string> ParseGame(string tel) {
  stringstream ss;
  ss << tel;
  vector<string> game_names;
  string name;

  // names are separated by '\n'
  while(getline(ss, name)) {
    if (name.size() == 0) {
      continue;
    } else {
      game_names.push_back(name);
    }
  }

  return game_names;
}

void PrintListOfGames(vector<string> listOfGames) {
  cout << "select game index to join:" << endl;
  vector<string>::iterator iter = listOfGames.begin();
  int i = 1;
  while (iter != listOfGames.end()) {
    string name = *iter;
    cout<<i<<". "<<name<<endl;
    iter++;
    i++;
  }
}
