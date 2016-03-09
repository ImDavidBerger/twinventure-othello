#include "player.h"
#include <iostream>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    this->board = new Board();
    this->side = side;
    this->testingMinimax = false;
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
    if(side == BLACK){
    	board->doMove(opponentsMove, WHITE);
  	}else{
  		board->doMove(opponentsMove, BLACK);
  	}
  	
  	Move *chosen = NULL;
  	if(testingMinimax){
  		Next temp = minimax(2);
  		return temp.move;
  	}
  	
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

void Player::updateBoard(char data[]){
	board->setBoard(data);
}

Next Player::minimax(int depth) {
	if(side == BLACK){
		return bestBlack(board, depth+1);
	}else{
		return bestWhite(board, depth+1);
	}
}





Next Player::bestBlack(Board * b, int depth){
	std::cerr << "Checking Black" << std::endl;
	if (depth == 0 || !b->hasMoves(BLACK)) {
		Next toReturn;
		toReturn.score = b->getScore(BLACK);
		toReturn.move = NULL;
		return toReturn;
	}
	
	Move* bestMove = NULL;
	int bestScore = -164;
	
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Move *m = new Move(r, c);
			//if it's a possible move
			if(board->checkMove(m, BLACK)){
				Board *temp = b->copy();
				temp->doMove(m, BLACK);
				
				Next tempNext = bestWhite(temp, depth-1);
				
				if (tempNext.score > bestScore) {
					bestScore = tempNext.score;
					bestMove = new Move(r, c);
				}
			}
		}
	}
	Next n;
	n.score = bestScore;
	n.move = bestMove;
	return n;
}






Next Player::bestWhite(Board * b, int depth){
	std::cerr << "Checking White" << std::endl;
	if (depth == 0 || !b->hasMoves(WHITE)) {
		Next toReturn;
		toReturn.score = b->getScore(WHITE);
		toReturn.move = NULL;
		return toReturn;
	}
	
	Move* bestMove = NULL;
	int bestScore = -164;
	
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Move *m = new Move(r, c);
			//if it's a possible move
			if(board->checkMove(m, WHITE)){
				Board *temp = b->copy();
				temp->doMove(m, WHITE);
				
				Next tempNext = bestBlack(temp, depth-1);
				
				if (tempNext.score > bestScore) {
					bestScore = tempNext.score;
					bestMove = new Move(r, c);
				}
			}
		}
	}
	Next n;
	n.score = bestScore;
	n.move = bestMove;
	return n;
}

/**

	
	//gets opponent's side
	Side opp;
	if (bside == WHITE) {
		opp = BLACK;
	}
	else {
		opp = WHITE;
	}
	
	//sets initial best score
	int bestScore;
	if (this->side == bside) {
		bestScore = -164;
	}
	else {
		bestScore = 164;
	}
	//check every possible move
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Move *m = new Move(r, c);
			//if it's a possible move
			if(board->checkMove(m, bside)){
				//create copy of board and do that move
				Board * temp = board->copy();
				temp->doMove(m, bside);
				
				//run minimax
				int score = minimax(temp, bside, depth-1, bestMove);
				//check if we want min score or max score
				if (this->side == bside) {
					if (score > bestScore) {
						bestScore = score;
						bestMove = new Move(r, c);
					}
				}
				else if (score < bestScore) {
					bestScore = score;
					bestMove = new Move(r, c);
				}
			}
		}
	}
	//bestMove now points to best move`
	return bestScore;
	
	*/
