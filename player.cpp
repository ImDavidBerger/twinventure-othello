#include "player.h"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    this->side = side;
    if (side == BLACK) {
		opp_side = WHITE;
	}
	else {
		opp_side = BLACK;
	}
	board = new Board();
    //hi!
    // GitHub is a potato
    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
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
 */
 /**********************************************************************************
  * STILL NEED TO ACCOUNT FOR TIME LEFT
  * ********************************************************************************/
Move *Player::doMove(Move *opponentsMove, int msLeft) {
	//check if we have time
	if (msLeft <= 0) 
	{
		return NULL;
	}
	//update board according to opponentsMove
	board->doMove(opponentsMove, opp_side);
	
	//if board has possible moves
	if (board->hasMoves(side)) 
	{
		//get list of possible moves
		vector<Move*> possMoves = board->getMoves(side);
		
		//iterate through vector to find best move
		vector::iterator i;
		Move * bestmove;
		int maxpts = 0;
		for (i = possMoves.begin(); i < possMoves.end(); i++) 
		{	
			//create copy of board, apply move, and check resulting score
			Board * copy = board->copy();
			copy->doMove(possMoves[i], side);
			if (copy->count(side) > maxpts) 
			{
				maxpts = copy->count(side);
				bestmove = possMoves[i];
			}
			delete copy;
		}
		return bestmove;
	}
    return NULL;
}
};
