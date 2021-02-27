// Sapir Kikoz 207071192

#include "Game.h"

#include <iostream>
#include <climits>
/*
 * This class will help the main program to lead the flow of the game
 * by switch turns and call to the game logic
 */
/*
 * This finction is the costructor of the game currently gets the
 * number that represents the turn of the current player
 */
Game::Game(int rows, int cols, ConsolePrinting* con,const char* filename): rows(rows), cols(cols), con(con) {
    this->filename = filename;
    this->gameBoard = new Board(rows, cols);
    //gameBoard->print();
    this->gamelogic = new GameLogic();
    this->moves= new int*[this->rows];
    for (int i = 0; i < this->rows; ++i)
        moves[i] = new int[this->cols];

    //assinging the matrix by the default values
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            this->moves[i][j] = 0;
        }
    }
   this->BlackDeafualtTurn = 1;
    //const char *filename = "settings.txt";

}

/*
 * this function returns the current board of the game
 */
Board* Game::GetBoard(){
    return this->gameBoard;
}
/*
 * this function returns the gameLogic of the game
 */
GameLogic* Game::getGameLogic() {
    return (GameLogic*)this->gamelogic;
}

int** Game::GetMoves(){
    return this->moves;
}

/*
 * player1 is the user player and player2 is the AI player
 */
void Game::gameFlow(Player* player1, Player* player2, int typeOfGame, ConsolePrinting* con){
    //x and y are the values that are scaned from the user
    this->player1 = player1;
    this->player2 = player2;
    int BhasposMoves = 1,WhasposMoves = 1;
    int gameStatus = 0;
    Cell* turnWorkedSuccessfully;
    int flafg_first_turn = 0;
    Cell* lastTurn;

    Player* cur_player = player1;
    do {

        con->currentBoard();
        con->print(this->gameBoard);

        gameStatus = gamelogic->checkWinner(gameBoard->getBoard());


    /*  if(flafg_first_turn == 1) {
          if (cur_player->GetplayerType() == Board::White) {
              con->xPlayed();
          } else {
              con->oPlayed();
          }
          con->printCell(lastTurn);
          con->newLine();
        }
*/
         cur_player->doTurn(typeOfGame, gameBoard, con, turnWorkedSuccessfully);
        //turnWorkedSuccessfully return 1 if
        // worked successfully, return 0 if didnt work

        if((turnWorkedSuccessfully->getI() == -1) &&
           (turnWorkedSuccessfully->getJ() == -1) &&
           (gameStatus == 0)) {
            if(cur_player->GetplayerType() == Board::Black){
                string anykey;
                con-> noPossibleMoves();
                std::getline(cin, anykey);
                con->newLine();
                //black player which is by default the first has no more posibble moves
                BhasposMoves = 0;
            } else {
                if(typeOfGame == 1){
                    string anykey;
                    con->noPossibleMovesForComp();
                    std::getline(cin, anykey);
                    con->newLine();
                    WhasposMoves = 0;
                } else if(typeOfGame == 2){
                    string anykey;
                    con-> noPossibleMoves();
                    std::getline(cin, anykey);
                    con->newLine();
                    //black player which is deafaultly the first has no more posibble moves
                    WhasposMoves = 0;
                }
            }
            cur_player = manageTurn(cur_player,player1,player2);
        }
        // gamestatus: if the game continue - 0, if draw - 1 ,if the black won - 2, if white won - 3
        if(gameStatus != 0){
            if(gameStatus == 1){
                con->currentBoard();
                con->print(gameBoard);
                con->writeDraw();
            } else if(gameStatus == 2){
                con->currentBoard();
                con->print(gameBoard);
                con->writeBlackWin();
            } else if(gameStatus == 3){
                con->currentBoard();
                con->print(gameBoard);
                con->writeWhiteWIn();
            }
            break;
        } else {
            //make valid move and switch turn
            int i = turnWorkedSuccessfully->getI(), j = turnWorkedSuccessfully->getJ();
            gamelogic->makeMove(gameBoard->getBoard(), i, j, cur_player->GetplayerType());
           // int memem = ;
           // lastTurn->setI(turnWorkedSuccessfully->getI());
           // lastTurn->setJ(turnWorkedSuccessfully->getJ());

            // this->lasturnI = turnWorkedSuccessfully->getI();
           // this->lasturnJ = turnWorkedSuccessfully->getJ();
            cur_player = (cur_player == player1) ? player2 : player1;//manageTurn(cur_player,player1,player2);
            //flafg_first_turn = 1;
        }
    } while (true);//this->numofmoves < 8 * 8 && this->invalidmoves < 2);
}


Player* Game::getFirstPlayer(){
    return this->player1;
}

Player* Game::getSecondPlayer(){
    return this->player2;
}

Player* Game::manageTurn(Player* givenPlayer,Player* currPlayer, Player* otherPlayer){
    //validmoves
    //int thereValidMoves;
    //thereValidMoves = givenPlayer->getGameLogic()->validMoves(givenPlayer->GetBoard()->GetMatrix(),givenPlayer->GetMoves(),givenPlayer);
    //send to ZeroMovesInCurrentTurn
    //if(thereValidMoves == 0){
    //}
    givenPlayer = (givenPlayer == currPlayer) ? otherPlayer : currPlayer;
    return givenPlayer;
}


Game::~Game(){
    for (int i = 0; i < this->rows; ++i)
        delete [] this->moves[i];
    delete [] this->moves;
}