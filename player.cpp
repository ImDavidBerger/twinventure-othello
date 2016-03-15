#include "player.h"

#include <unistd.h>
#include <iostream>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    this->board = new Board();
    if(side == BLACK){
    	this->side = true;
    }else{
    	this->side = false;
    }
    this->move = 0;
    this->board->StartBoard();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 Move: 4, 7Score: 60
+----------------+
|  X X X         |
|X X X           |
|  O X X         |
|X O X X X       |
|X O X X X       |
|X O X     X     |
|X   O           |
|X   X X X       |
+----------------+
Opponents move: 4, 1
Picked 3 move.


Move: 4, 1Score: 47
+----------------+
|  X X O         |
|X X X   O       |
|  O X O         |
|X O O X X       |
|X O X X X       |
|X O X     X     |
|X   O           |
|X   X X X       |
+----------------+

 */
 /**********************************************************************************
  * STILL NEED TO ACCOUNT FOR TIME LEFT
  * ********************************************************************************/
Move* Player::doMove(Move *opponentsMove, int msLeft) {
	if(opponentsMove != NULL){
		Posn m;
		if(!side && move == 0) board->nextGen();
		m.x = opponentsMove->getX();
		m.y = opponentsMove->getY();
		int index = board->findChild(m);
		board = board->getNext()[index];
	}else{
		if(move != 0){
			board->nextTurn();
			board->clearNext();
			board->createGens(2);
		}
	}
	board->printBoard();
	
	sleep(0);
    Move *chosenMove = NULL;
    
    if(board->getValidMoves().size() == 0){
    	sleep(3);
    	return NULL;
    }
    if(move == 0){
    	board->createGens(4);
    }else{
    	board->createGens(2);
    }
    Posn m = board->getBestMove(-1);
    
    chosenMove = new Move(m.x, m.y);
	int chosen = board->findChild(m);
    board = board->getNext()[chosen];
    //cerr << "Trying move to " << m.x << ", " << m.y << "." << endl;
    //board->printBoard();
	board->printBoard();
    
    move++;
    return chosenMove;
}
