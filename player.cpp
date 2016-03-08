#include "player.h"
#include <iostream>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    this->board = new Board();
    this->side = side;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
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
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    if(side == BLACK){
    	board->doMove(opponentsMove, WHITE);
  	}else{
  		board->doMove(opponentsMove, BLACK);
  	}
  	
  	Move *chosen, *bestStart, *currentStart;
  	int chosenScore = -168, tempScore;
  	Board *temp;
  	
  	if(!board->hasMoves(side)){
  		return NULL;
  	}
  	
  	for(int r = 0; r < 8; r++){
  		for(int c = 0; c < 8; c++){
  			if(board->checkMove(new Move(r, c), side)){
  				temp = board->copy();
  				temp->doMove(new Move(r, c), side);
  				tempScore = temp->getScore(side);
  				if(tempScore > chosenScore){
  					chosen = new Move(r, c);
  					chosenScore = tempScore;
  				}
  			}
  		}
  	}
  	
  	// std::cerr << chosenScore << std::endl;
  	board->doMove(chosen, side);
    return chosen;
}
