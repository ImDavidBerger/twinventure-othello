#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
using namespace std;

class Player {
private:
	Side side;
public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
	Board * board;
	Next minimax(int depth);
	Next bestBlack(Board * b, int depth);
	Next bestWhite(Board * b, int depth);
	void updateBoard(char data[]);
};

#endif
