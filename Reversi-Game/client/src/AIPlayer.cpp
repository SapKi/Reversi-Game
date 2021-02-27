//
// Created by sapir on 25/11/17.
//

#include "AIPlayer.h"
#include <climits>
#include <iostream>

// instead of sending the game to the constractor you send game->secoungPlater
AIPlayer::AIPlayer(Board* board, GameLogic* logic, int** validMoves , Board::State playerChar,Player* humanPlayer,int typeOfGame,ConsolePrinting* con,
const char* filename)
        : Player(board,logic,validMoves,playerChar,typeOfGame,con,filename) {
    this->typeOfGame = typeOfGame;
    this->realBoard = board;
    this->copyBoard = new Board(this->realBoard);
    this->copyLogic = logic;
    this->moves = validMoves;
    //we want the user player which is the first player f the game to be the opponent
    this->opponent = humanPlayer;
    this->opponentmoves = humanPlayer->GetMoves();
    //assinging the moves array of the opponent to zero to help thaey wont
    //use the same arraey of moves in the function of building the new imaginary board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            this->opponentmoves[i][j] = 0;
        }
    }
    //for(int i = 0; i < 64; i++){
    //    this->arrayofmaxvalidmoves[i] = NULL;
    //}
    //for(int i = 0; i < 64; i++){
    //    this->arrayofCells[i] = NULL;
    //}
    this->goldenIndex = 0;
    this->finalI = 0;
    this->finalJ = 0;
}

void AIPlayer::PrintCurrentStatus(Board::State playerChar, int i, int j) {

}

void AIPlayer::finishGame() {

}

void AIPlayer::connectToServer() {

}

int AIPlayer::getMoveFromServer() {
    return 0;
}

void AIPlayer::noMove(ConsolePrinting *con) {

}

int AIPlayer::retFinalI(){
    return this->finalI;
}

int AIPlayer::retFinalJ(){
    return this->finalJ;
}

/*
 * returns 1 if the best move worked successfully
 * 0 - if there are no possible moves and the turn should pass tothe other player
 */
void AIPlayer::doTurn(int typeOfGame,Board* board, ConsolePrinting* con, Cell *&c) {
    int minmax = INT_MAX;
    int goldenIndex = 0;
    this->con = con;

    Board* RealBoard = board;
    Board* CopyBoard = new Board(board);
    GetBestScore(CopyBoard);

    bool isThereMoves = copyLogic->validMoves(RealBoard->getBoard(), this->moves, this->GetplayerType());
    if (isThereMoves){
        //moves to the Game!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
        //copyLogic->makeMove(RealBoard->getBoard(), this->finalI, this->finalJ, this->GetplayerType());
        //the function returns 1 if we had a successful turn
        this->finalI;
        this->finalJ;
        /// we need to call one function of the AI//////////////////////////////////
        //we need to send back finalI, finalJ, and playertype
        //PrintCurrentStatus(this->opponent->GetplayerType(),this->finalI,this->finalJ);
        c = new Cell(finalI,finalJ);
    } else {
        c = new Cell(-1,-1);
    }
}

void AIPlayer::GetBestScore(Board* CopyBoard){
    int minscore = INT_MAX;
    // Cell maxScoreCell(0,0);
    int currentscorefrompossiblemove = 0;
    bool isThereMoves = copyLogic->validMoves(CopyBoard->getBoard(), this->moves, this->GetplayerType());
    if(isThereMoves) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (this->moves[i][j] == 1) {
                    currentscorefrompossiblemove = buildImaginaryBoardforAI(CopyBoard, i, j);
                    if (currentscorefrompossiblemove < minscore) {
                        minscore = currentscorefrompossiblemove;
                        this->finalI = i;
                        this->finalJ = j;
                    }
                }
            }
        }
    }
}



/*
 * this function will do the fake move on the fake board and count the best
 * score for each player
 * **************our current player is default the white player
 */
int AIPlayer::buildImaginaryBoardforAI(Board* Copyboard,int i, int j){
    Player* curPlayer = this;
    int maxscore = INT_MIN;
    int currentscorefrompossiblemoveopponent = 0;
    int istheremovesfortheXplayer = 0;
    Board* imaginaryBoard = new Board(Copyboard);
    //this is the first move of the Ai
    copyLogic->makeMove(imaginaryBoard->getBoard(), i, j, this->GetplayerType());
    copyLogic->validMoves(imaginaryBoard->getBoard(),opponentmoves,opponent->GetplayerType());
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            if(this->opponentmoves[i][j] == 1) {
                Board* imaginaryBoardForHuman = new Board(imaginaryBoard);
                currentscorefrompossiblemoveopponent = buildImaginaryBoardforOpponent(imaginaryBoardForHuman,i,j);
                if(currentscorefrompossiblemoveopponent > maxscore){
                    maxscore = currentscorefrompossiblemoveopponent;
                }
            }
        }
    }
    return maxscore;
}

int AIPlayer::buildImaginaryBoardforOpponent(Board* copyboard,int i, int j) {
    int countercurrent = 0, counteropponent = 0;
    Board* imaginaryBoard = copyboard;
    copyLogic->makeMove(imaginaryBoard->getBoard(), i, j, this->opponent->GetplayerType());

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            countercurrent += (imaginaryBoard->getBoard()[row][col] == 'O');
            counteropponent += (imaginaryBoard->getBoard()[row][col] == 'X');
        }
    }
    //we switched again the turn
    //copyLogic->manageTurn(opponent,opponent,this);
    //'x'-'0'
    //cout<<countercurrent<<"-x,"<<counteropponent<<"-o";
    return counteropponent-countercurrent;
}
