//
// Created by sapir on 10/12/17.
//

#include "FirstClient.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <limits>
#include <cstdlib>
#include <climits>
#include <sstream>

FirstClient::FirstClient(Board* board, GameLogic* logic, int** validMoves, Board::State playerChar, int typeOfGame,ConsolePrinting* con,
                           const char* filename): Player(board,logic,validMoves,playerChar,typeOfGame,con,filename), con(con) {
    this->copyBoard = board;
    this->copyLogic = logic;
    this->moves = validMoves;
    this->typeOfGame = typeOfGame;
}

void FirstClient::connectToServer() {
    // Create a socket point
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP.c_str(), &address)) {
        throw "Can't parse IP address";
    }
    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
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
    ////////////////playerChoose();
}

void FirstClient::UpdateArgs(int firstarg, int secondarg) {
    ssize_t numToSend;
    // Write 2 numbers t
    numToSend = write(clientSocket, &firstarg, sizeof(firstarg));
    if (numToSend == -1) {
        throw "Error writing arg1 to socket";
    }
    numToSend = write(clientSocket, &secondarg, sizeof(secondarg));
    if (numToSend == -1) {
        throw "Error writing arg2 to socket";
    }

}

void FirstClient::doTurn(int typeOfGame, Board *board, ConsolePrinting *con, Cell *&c) {
    //x and y are the values that are scaned from the user
    int y = 0, x = 0;
    char xchar, ychar;
    char dummy = ' ';

    bool isThereMoves = copyLogic->validMoves(copyBoard->getBoard(), this->moves, this->GetplayerType());

    con->itsYourMove(this->GetplayerType());
    con->possibleMoves(this->moves);
    cout<<"Please enter your move row,col:";
    // now we check if the inserted values are valid in the array
    if (isThereMoves) {
        while (true) {

            cin >>x >>dummy>>y;
            xchar = x;
            ychar = y;

            if (xchar > 8 || xchar < 1 || ychar < 1 || ychar > 8 || (dummy != ',')) {
                cout << "invalid value, please enter 'row,col' between 1-8" << endl;
                cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                continue;
            }


            // we got ints.
            // player starts from 1. our board starts from 0
            x-=1;
            y-=1;
            if(InvalidInValidArray(x,y) != 1){
                cout << "your move is not possible, please enter a move from the showed possible moves" << endl;
                cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                continue;
            }

            if (copyLogic->checkInput(copyBoard->getBoard(), x, y))
                break;
        }
        // p->setI(x);
        // p->setJ(y);

        //moves to the game!!!!!!!!!!!

        //if the turn worked succesfully
        c = new Cell(x,y);

        // send to server
        stringstream ss;
        ss << x;
        ss << ",";
        ss << y;
        write(clientSocket, ss.str().c_str(), ss.str().size()+1);
    } else {
        //bad arguments if the turn failed
        c = new Cell(-1,-1);
        // send to server
        string no_move_msg = "NoMove";
        write(clientSocket, (void *)(no_move_msg.c_str()), strlen(no_move_msg.c_str()) + 1);
    }
}

int FirstClient::InvalidInValidArray(int x, int y) {
    if(this->moves[x][y] == 1) {
        return 1;
    } else {
        return 0;
    }
}

int FirstClient::getMoveFromServer() {
    ssize_t n;
    // Read the result from the server
    char msg[10];
    n = read(clientSocket, msg, sizeof(msg));
    if (n == -1) {
        throw "Error reading result from socket";
    }

    return  atoi(msg);
}

void FirstClient::noMove(ConsolePrinting* con) {
    string anyKey;
    con->noMorePosMove(this->GetplayerType());
    con->pressAnyKeyToCont();
    getline(cin, anyKey);
    getline(cin, anyKey);
    con->newLine();
    UpdateArgs(-1, -1);
}

void FirstClient::finishGame() {
    int result = -2;
    ssize_t n;

    string end_str = "EndGame";
    n = write(this->clientSocket, end_str.c_str(), sizeof(end_str));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    close(this->clientSocket);
}


/*
void FirstClient::playerChoose() {
    string command, name;
    int choose, n;
    int check1 = 0;
    int check2 =0;
    while(check1==0) {
        con->printClientMenu();
        cin >> choose;
        while (check2 == 0) {
            cin>>choose;
            cout<<endl;
            if(choose != 1 && choose!= 2 && choose!= 3) {
                con->noValidOption();
            } else check2 = 1;
        }
        switch (choose) {
            case 1: {
                con->chooseGameOptions();
                cin >> name;
                command = "start ";
                command = command + name;
                WriteToServer(command);
                string checkCommand = ReadFromServer(<#initializer#>);
                cin.ignore();
                if (checkCommand == "Exist") {
                    con->printString(checkCommand);
                    close(this->clientSocket);
                    connectToServer();
                } else {
                    check1 = 1;
                }
                break;
            }
            case 2: {
                command = "list_games";
                WriteToServer(command);
                string receivedMessage = ReadFromServer(<#initializer#>);
                con->printString(receivedMessage);
                close(this->clientSocket);
                break;
            }

            case 3: {
                con->EnterNameOfGame();
                command = "join ";
                command = command + name;
                WriteToServer(command);
                string checkCommand;
                = ReadFromServer(<#initializer#>);
                cin.ignore();
                if (checkCommand == "UnavailableGame") {
                    con->printString(checkCommand);
                    close(this->clientSocket);
                    connectToServer();
                } else {
                    check1 = 1;
                }
                break;
            }
            default: {
                con->printString(" Input invalid,  try again.");
            }
        }
    }
}
*/

int FirstClient::WriteToServer(string command) {
    //char commandBuffer[50] = {0};
    int check = send(clientSocket, (char *)command.c_str(), command.size()+1, 0);
    if (check == -1) {
        //throw "Error writing to server";
        cout << "Error writing to server" << endl;
    } else if (check == 0) {
        con->printString("Server disconnected");
    }
    return check;
}

int FirstClient::ReadFromServer(string &command_str) {
    char command[50] = {0};
    int r = recv(clientSocket, &command, sizeof(command), 0);
    if (r == -1) {
        con->printString("Error reading result from socket");
    } else if (r == 0) {
        con->printString("Server disconnected");
    }
    command_str = string(command);
    return r;
}