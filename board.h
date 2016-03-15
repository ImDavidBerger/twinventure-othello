#ifndef __board_h__
#define __board_h__


#include "shared.h"
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

class Board {
   
private:
    bitset<16> board[8];
    short score;
    bool turn;
    Posn genMove;
    vector<Board*> next;
    
    bool onBoard(int x, int y);
    void createChild(Posn m);
    
    void updateColorsBlack(Posn m);
    void updateColorsWhite(Posn m);
    
    bool isValidBlackMove(Posn m);
    bool isValidWhiteMove(Posn m);
    
    short endOfBlackTunnel(int depth);
    short endOfWhiteTunnel(int depth);
      
public:
    Board();
    void StartBoard();
    ~Board();
    Board *copy();
    
    bitset<2> getSquare(short x, short y);
    void setSquare(short x, short y);
    void overWrite(bitset<16> b[]);
    
    Posn getCreator();
    void tellCreator(Posn m);
    
    short getScore();
    void updateScore();
    
    void flipSquare(short x, short y);
    void updateColors(Posn m);
    
    void nextTurn();
    void clearNext();
    
    
    bool isValidMove(Posn m);
    vector<Posn> getValidMoves();
    
    
    vector<Board*> getNext();
    void nextGen();
    void createGens(int depth);
    Posn getBestMove(int depth);
    int findChild(Posn m);
    
    bool isDone();
    void printBoard();
};

#endif
