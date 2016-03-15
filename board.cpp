#include "board.h"

using namespace std;

    Board::Board(){
        for(int i = 0; i < 8; i++){
            board[i].reset();
        }
        score = 0;
        turn = true;
    }
    
    
    
    void Board::StartBoard(){
		setSquare(3, 4);
		setSquare(4, 3);
		nextTurn();
		setSquare(3, 3);
		setSquare(4, 4);
		nextTurn();
	}
    
    
    
    Board::~Board(){
        for(unsigned int i = 0; i < next.size(); i++){
            delete next[i];
        }
    }
    
    
    
    void Board::clearNext(){
    	next.clear();
    }
    
    
    
    void Board::nextTurn(){
    	turn = !turn;
    }
    
    
    
    Posn Board::getCreator(){
    	return genMove;
    }
    
    void Board::tellCreator(Posn m){
    	genMove = m;
    }
    
    
    
    bitset<2> Board::getSquare(short x, short y){
        bitset<2> value;
        
        value.set(0, board[y][2*x]);
        value.set(1, board[y][2*x + 1]);
        return value;
    }
    
    
    
    short Board::getScore(){
    	return score;
    }
    
    
    
    vector<Board*> Board::getNext(){
    	return next;
    }
    
  	
    
    /**
    	Sets a given square to the specified color
    	true: black
    	false: white
    */
    void Board::setSquare(short x, short y){
        if(turn){
            board[y].set(2*x, 1);
            board[y].set(2*x+1, 0);
        }else{
            board[y].set(2*x, 0);
            board[y].set(2*x+1, 1);
        }
    }
    
    
    
    // flips the color of a square. Do not call on blank square
    void Board::flipSquare(short x, short y){
        board[y][2*x].flip();
        board[y][2*x + 1].flip();
    }
    
    
    
    // updates the score of our board
    void Board::updateScore(){
    	short a = 200, b = 10, c = -20, d = -1, e = 3, f = 5;
    	//short a = 200, b = 10, c = -20, d = -1, e = 3, f = 5;
		vector<short> weights = {a,c,b,b,b,b,c,a,
								 c,c,d,d,d,d,c,c,
								 b,d,f,e,e,f,d,b,
								 b,d,e,e,e,e,d,b,
								 b,d,e,e,e,e,d,b,
								 b,d,f,e,e,f,d,b,
								 c,c,d,d,d,d,c,c,
								 a,c,b,b,b,b,c,a};
	    
    	for(int r = 0; r < 8; r++){
    		for(int c = 0; c < 8; c++){
    			if(board[c][2*r] == 1){
    				score += weights[8*c + r];
    			}else if(board[c][2*r+1] == 1){
    				score -= weights[8*c + r];
    			}
    		}
    	}
    }
    
    
    
    // checks if a move is on the board
    bool Board::onBoard(int x, int y){
        return (0 <= x) && (x <= 7) && (0 <= y) && (y <= 7);
    }
    
    
    
    /*
     @brief: decides whether to call updateColorsBlack or updateColorsWhite 
     based on who made the last turn
     
     @param: Posn m - the move made
     */
    void Board::updateColors(Posn m){
        if(turn){
            updateColorsBlack(m);
        }else{
            updateColorsWhite(m);
		}
	}
    
    
    
    /*
     @brief: Updates the pieces on the board after a black move
     
     @param: Posn m - the move done by black
     */
    void Board::updateColorsBlack(Posn m){
		int r, c;
        for(int dx = -1; dx <= 1; dx++){
        	for(int dy = -1; dy <= 1; dy++){
        		if(dx == 0 && dy == 0) continue;
        		
        		r = m.x + dx;
		    	c = m.y + dy;
		    	while(onBoard(r, c) && board[c][2*r+1] == 1){
		    		r += dx;
		    		c += dy;
		    	}
		    	if(onBoard(r, c) && board[c][2*r] == 1){
					r -= dx;
					c -= dy;
					while(board[c][2*r+1] == 1){
						flipSquare(r, c);
						r -= dx;
						c -= dy;
					}
				}
		    }
		}
	}
    
    
    
    /*
     @brief: Updates the pieces on the board after a white move
     
     @param: Posn m - the move done by white
     */
    void Board::updateColorsWhite(Posn m){
		int r, c;
        for(int dx = -1; dx <= 1; dx++){
        	for(int dy = -1; dy <= 1; dy++){
        		if(dx == 0 && dy == 0) continue;
        		
        		r = m.x + dx;
		    	c = m.y + dy;
		    	while(onBoard(r, c) && board[c][2*r] == 1){
		    		r += dx;
		    		c += dy;
		    	}
		    	if(onBoard(r, c) && board[c][2*r+1] == 1){
		    		r -= dx;
		    		c -= dy;
					while(board[c][2*r] == 1){
						flipSquare(r, c);
						r -= dx;
						c -= dy;
					}
				}
			}
		}
	}
	
	
	
	bool Board::isValidMove(Posn m){
		if(turn){
			return isValidBlackMove(m);
		}else{
			return isValidWhiteMove(m);
		}
	}
	
	
	
	bool Board::isValidBlackMove(Posn m){
		if(board[m.y][2*m.x] == 1 || board[m.y][2*m.x+1] == 1){
			return false;
		}
		int r, c, possible;
        for(int dx = 1; dx >= -1; dx--){
        	for(int dy = 1; dy >= -1; dy--){
        		if(dx == 0 && dy == 0) continue;
        		
        		possible = 0;
        		r = (int)m.x + dx;
		    	c = (int)m.y + dy;
		    	while(onBoard(r, c) && board[c][2*r+1] == 1){
					possible++;
					r += dx;
					c += dy;
				}
		    	if(onBoard(r, c) && board[c][2*r] == 1 && possible > 0){
					return true;
				}
		    }
		}
		return false;
	}
	
	
	
	bool Board::isValidWhiteMove(Posn m){
		if(board[m.y][2*m.x] == 1 || board[m.y][2*m.x+1] == 1){
			return false;
		}
		int r, c, possible;
        for(int dx = 1; dx >= -1; dx--){
        	for(int dy = 1; dy >= -1; dy--){
        		if(dx == 0 && dy == 0) continue;
        		
        		possible = 0;
        		r = (int)m.x + dx;
		    	c = (int)m.y + dy;
		    	while(onBoard(r, c) && board[c][2*r] == 1){
					possible++;
					r += dx;
					c += dy;
				}
		    	if(onBoard(r, c) && board[c][2*r+1] == 1 && possible > 0){
					return true;
				}
		    }
		}
		return false;
	}
	
	
	
	vector<Posn> Board::getValidMoves(){
		vector<Posn> valid;
		
		Posn m;
		for(short r = 0; r < 8; r++){
			for(short c = 0; c < 8; c++){
				m.x = r;
				m.y = c;
				if(isValidMove(m)){
					Posn add;
					add.x = r;
					add.y = c;
					valid.push_back(add);
				}
			}
		}
		
		return valid;
	} 
	
	
	
	// sets the board to a given set of values
	void Board::overWrite(bitset<16> b[]){
		for(short i = 0; i < 8; i++){
			board[i] = b[i];
		}
	}
    
    
    
    /**
	Creates a new child for the current board. The child contains the 
	current board with one more move applied, an updated score and a 
	flipped turn.
	*/	
    void Board::createChild(Posn m){
		Board *child = new Board();
		child->tellCreator(m);
		child->overWrite(board);
		if(!turn){
			child->nextTurn();
		}
		child->setSquare(m.x, m.y);
		child->updateColors(m);
		child->updateScore();
		child->nextTurn();
		next.push_back(child);
	}
	
	
	
	void Board::nextGen(){
		vector<Posn> moves = getValidMoves();
		if(moves.size() == 0){
			Board* pass = new Board;
			pass->overWrite(board);
			pass->updateScore();
			pass->nextTurn();
			next.push_back(pass);
			cerr << "Created a pass board\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
		}else{	
			for(unsigned int i = 0; i < moves.size(); i++){
				createChild(moves[i]);
			}
		}
	}
	
	
	
	void Board::createGens(int depth){
//		if(isDone()){
//			return;
//		}
		if(next.size() == 0 && depth > 0){
			nextGen();
			if(depth > 1){
				for(unsigned int i = 0; i < next.size(); i++){
					next[i]->createGens(depth - 1);
				}
			}
		}else if(next.size() > 0 && depth > 0){
			for(unsigned int i = 0; i < next.size(); i++){
				next[i]->createGens(depth);
			}
		}
	}
	
	
	
	int Board::findChild(Posn m){
		for(unsigned int i = 0; i < next.size(); i++){
			Posn creator = next[i]->getCreator();
			if(m.x == creator.x && m.y == creator.y){
				return i;
			}
		}
		return -1;
	}
	
	
	
	Posn Board::getBestMove(int depth){
		short best;
		unsigned int bestLoca = 0;
		if(turn){
			best = -10000;
			for(unsigned int i = 0; i < next.size(); i++){
				if(next[i]->endOfBlackTunnel(depth-1) > best){
					best = next[i]->endOfBlackTunnel(depth-1);
					bestLoca = i;
				}
			}
			return next[bestLoca]->getCreator();
		}else{
			best = 10000;
			for(unsigned int i = 0; i < next.size(); i++){
				if(next[i]->endOfWhiteTunnel(depth-1) < best){
					best = next[i]->endOfWhiteTunnel(depth-1);
					bestLoca = i;
				}
			}
			return next[bestLoca]->getCreator();
		}
	}
		
		
		
	short Board::endOfBlackTunnel(int depth){
		if(depth == 0 || next.size() == 0){
			return score;
		}
		
		unsigned int location = 0;
		short best = 10000;
		for(unsigned int i = 0; i < next.size(); i++){
			if(next[i]->getScore() < best){
				best = next[i]->getScore();
				location = i;
			}
		}
		return next[location]->endOfWhiteTunnel(depth - 1);
	}
	
	
	
	short Board::endOfWhiteTunnel(int depth){
		if(depth == 0 || next.size() == 0){
			return score;
		}
		
		unsigned int location = 0;
		short best = -10000;
		for(unsigned int i = 0; i < next.size(); i++){
			if(next[i]->getScore() > best){
				best = next[i]->getScore();
				location = i;
			}
		}
		return next[location]->endOfBlackTunnel(depth - 1);
	}

    void Board::printBoard(){
        cerr << "\n\nMove: " << genMove.x << ", " << genMove.y
        	 << "Score: " << score << endl;
        cerr << "+----------------+" << endl;
        for(int i = 0; i < 8; i++){
            cerr << "|";
            for(int j = 0; j < 8; j++){
                if(board[i][2*j] == 1){
                    cerr << "X ";
                }else if(board[i][2*j+1] == 1){
                    cerr << "O ";
                }else{
                    cerr << "  ";
                }
            }
            cerr << "|" << endl;
        }
        cerr << "+----------------+" << endl;
    }
    
    bool Board::isDone(){
    	if(getValidMoves().size() > 0){
    		return false;
    	}
    	Board *copy = new Board();
    	copy->overWrite(board);
    	if(turn){copy->nextTurn();}
    	if(copy->getValidMoves().size() > 0){
    		return false;
    	}
    	return true;
	}
	
	
	
	/*
int main(){
	Board b = Board();
	cerr << b.getSquare(3, 3) << endl;
	b.setSquare(3, 3);
	b.setSquare(4, 4);
	b.nextTurn();
	b.setSquare(3, 4);
	b.setSquare(4, 3);
	b.nextTurn();
	b.printBoard();
	
	
	
	Posn m;
	
	m.x = 2;
	m.y = 4;
	cerr << b.isValidMove(m) << endl;
	b.setSquare(2, 4);
	b.updateColors(m);
	b.updateScore();
	b.nextTurn();
	
	b.printBoard();
	
	b.nextGen();
	vector<Board*> Next = b.getNext();
	for(unsigned int i = 0; i < Next.size(); i++){
		cerr << "Possibility " << i+1 << endl;
		Next[i]->printBoard();
	}
	int val;
	cerr << "Please enter your next choice:" << endl;
	cin >> val;
	
	while(val){
		if(val > Next.size()){
			cerr << "Value greater than possibilites. Try again\n" << endl;
		}else{
			b = *Next[val-1];
		
			b.printBoard();
			b.nextGen();
			Next = b.getNext();
			for(unsigned int i = 0; i < Next.size(); i++){
				cerr << "Possibility " << i+1 << endl;
				Next[i]->printBoard();
			}
		}
		
		cerr << "Please enter your next choice:" << endl;
		cin >> val;
	}
	cerr << "Please enter an x.y" << endl;
	float val;
	cin >> val;
	short x = (short)val;
    short y = (short)(10*val) - (10 * x) ;
	while(val){
    	x = (short)val;
    	y = (short)(10*val) - 10 * x;
    	m.x = x;
    	m.y = y;
    	if(b.isValidMove(m)){
			b.setSquare(x, y);
			b.updateColors(m);
			b.updateScore();
			b.nextTurn();
			b.printBoard();
	    }else{
	    	std::cerr << "Invalid Move. Please enter valid move\n" << std::endl;
	    }
	    
    	cerr << "Please enter an x.y" << endl;
	    cin >> val;
    }
}
    */
