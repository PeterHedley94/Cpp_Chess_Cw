#include <iostream>
#include "pieces.h"
#include "ChessBoard.h"
#include <string>

using namespace std;


ChessBoard :: ChessBoard(){
  BCheck = false;
  WCheck = false;
  for(int m=0; m<8; m++){
    for(int n=0; n<8; n++)
      board_[m][n] = NULL;
  }
  moved_piece_ = NULL;
  taken_piece_ = NULL;
  turn_ = ' ';
  populateBoard();
  gameOver_ = false;
}

ChessBoard :: ~ChessBoard(){
  clearBoard();
  delete moved_piece_;
  delete taken_piece_;
}

//Checks for a Blocking Piece
bool ChessBoard::checkRoute() const{
  for(int i=1; i<8 ; i++){
    if(routeUp_[i+1] == -1) return true;
    if( board_[routeUp_[i]][routeAcross_[i]] != NULL) return false;
  }
  cout << "Went Wrong\n";
  return false;
}

//Check Input is in correct format
err ChessBoard :: checkInput(const string start,const string end){
  int numberAtArray0 = '8', alphaA = 'A';
  
  if(start.length() != 2 || !isalpha(start[0]) ||
     !isdigit(start[1]) || !isupper(start[0])){return (IncorrectStartSquare);}
  if(end.length() != 2 || !isalpha(end[0]) ||
     !isdigit(end[1]) || !isupper(end[0])){ return (IncorrectEndSquare);}

  routeUp_[0] = (numberAtArray0-static_cast<int>(start[1]));
  routeUp_[1] = (numberAtArray0-static_cast<int>(end[1]));
  routeAcross_[0] = static_cast<int>(start[0]) - alphaA;
  routeAcross_[1] = static_cast<int>(end[0]) - alphaA;
  return NoError;
}


err ChessBoard :: checkInBoard() const{

  if(routeUp_[0] > 7 || routeAcross_[0] > 7 ||
     routeUp_[0] < 0 || routeAcross_[0] < 0){
    return StSqOutBoard;
  }

  if(routeUp_[1] > 7 || routeAcross_[1] > 7 ||
     routeUp_[1] < 0 || routeAcross_[1] < 0){
    return ESqOutBoard;
  }

  if(routeUp_[0] == routeUp_[1] && routeAcross_[0] == routeAcross_[1]){
    return SameSqr;
  }
  return NoError;
}

void ChessBoard :: clearBoard(){
  BCheck = false;
  WCheck = false;
  moved_piece_ = NULL;
  taken_piece_ = NULL;
  gameOver_ = false;
  turn_ = ' ';
  for(int m=0; m<8; m++){
    for(int n=0; n<8; n++){
      if(board_[m][n] != NULL){
        delete board_[m][n];
        board_[m][n] = NULL;
      }
    }
  }
}

void ChessBoard :: populateBoard(){
  cout << "A new chess game is started!" << endl;
  for(int m=7; m>=0; m -= 7){
    for(int n=0; n<8; n++){

      switch(n){
      case 0:
      case 7:
	board_[m][n] = new Rook(m,n);
	break;
      case 1:
      case 6:
	board_[m][n] = new Knight(m,n);
	break;
      case 2:
      case 5:
	board_[m][n] = new Bishop(m,n);
	break;
      case 3:
	board_[m][n] = new Queen(m,3);
	break;
      case 4:
	board_[m][n] = new King(m,4);
        break;
      }
    }
   }

  BKingLoc_[0] = 0;
  BKingLoc_[1] = 4;
  WKingLoc_[0] = 7;
  WKingLoc_[1] = 4;

  for(int m=1; m<7; m += 5){
    for(int n=0; n<8; n++){
      board_[m][n] = new Pawn(m,n);
    }
  }
}


int ChessBoard :: submitMove(const string start, const string end){
  err code = NoError;
  if(gameOver_) code = GameOver;
  if(code == NoError)
    code = checkInput(start,end);
  if(code >= NoError)
    code = InitiateMove(true);
  
  if(code >= NoError || code <=BInCheck){
    if(checkStale('B')){
      if(code == BInCheck){
        code = BChMate;
      }else{
        code = StaleMate;
      }
    }
    if(checkStale('W')){
      if(code == WInCheck){
	code = WChMate;
      }else{
	code = StaleMate;
      }
    }
  }

  printMessage(code,start,end);

  if(taken_piece_ != NULL){
    delete taken_piece_;
    taken_piece_ = NULL;
  }
  return (0);
}


err ChessBoard::InitiateMove(bool complete_move){
  bool piece_in_loc = false;
  piece_ptr piece_to_move = NULL, move_to_square = NULL;
  int end_square[2],start_square[2];
  err code = checkInBoard();
  if(code!= NoError) return code;

  piece_to_move = board_[routeUp_[0]][routeAcross_[0]];
  move_to_square = board_[routeUp_[1]][routeAcross_[1]];
  start_square[0] = routeUp_[0];
  start_square[1] = routeAcross_[0];
  end_square[0] = routeUp_[1];
  end_square[1] = routeAcross_[1];

  if(turn_ == ' ' && start_square[0] < 5) turn_ = 'B';
  if(turn_ == ' ' && start_square[0] >= 5) turn_ = 'W';

  if(piece_to_move == NULL){return(NoPiece);}
  if(move_to_square != NULL){piece_in_loc = true;}

  if(piece_in_loc){
    if(move_to_square->getSymbol() == 'K' && complete_move == true){return(TakeKing);}
    if(piece_to_move->getColour() ==
       move_to_square->getColour()){return(TakeSameCol);}
  }
  if(!(piece_to_move->move(routeUp_,routeAcross_,piece_in_loc))){return(InvalidMove);}
  if(!(checkRoute())){return(BlockPiece);}
  

  board_[end_square[0]][end_square[1]] = piece_to_move;
  board_[start_square[0]][start_square[1]] = NULL;


  code = checkCheck(piece_to_move,move_to_square,start_square,end_square,complete_move);
  if(code != NoError &&  code > BInCheck){
    reset_move(piece_to_move,move_to_square,start_square,end_square);
    return(code);
  }

  if(!complete_move){
    reset_move(piece_to_move,move_to_square,start_square,end_square);
    return(code);
  }

  if(piece_in_loc){
    taken_piece_ = move_to_square;
  }else{
    taken_piece_ = NULL;
  }
  moved_piece_ = piece_to_move;
  return(code);
}

//Check if a square can be attacked by a certain colour
bool ChessBoard::attackingSquare(const char colour, int sq[2]){
  bool turn_change = false;
  if(turn_ != colour){
    changeTurn();
    turn_change = true;
  }

  for(int m=-8; m<8; m++){
    for(int n=-8; n<8; n++){
      routeUp_[0] = m+sq[0];
      routeAcross_[0] = n+sq[1];
      if(routeUp_[0] >= 0 && routeUp_[0]<= 7 &&
	 routeAcross_[0] >= 0 && routeAcross_[0]<= 7){
	routeUp_[1] = sq[0];
	routeAcross_[1] = sq[1];

	if(board_[routeUp_[0]][routeAcross_[0]] != NULL){
	  if(board_[routeUp_[0]][routeAcross_[0]]->getColour() == colour){
	    int init_move = InitiateMove(false);
	    if(init_move == 0){
	      if(turn_change) changeTurn();
	      return true;
	    }
	  }
	}
      }
    }
  }
  if(turn_change) changeTurn();
  return false;
}

void ChessBoard:: changeTurn(){
  if(turn_ == 'W'){
    turn_ = 'B';
  }else if(turn_ == 'B'){
    turn_ = 'W';
  }
}

//If not pieces of a colour can make a legal move that colour is in stale mate
bool ChessBoard::checkStale(char colour){

  for(int m=0; m<8; m++){
    for(int n=0; n<8; n++){
      int temp[2] = {m,n};
      if(attackingSquare(colour,temp)){
	return false;
      }
    }
  }
  return true;
}

void ChessBoard::reset_move(piece_ptr piece_to_move,piece_ptr move_to_square,
			    int start_square[2],int end_square[2]){

  if(piece_to_move->getSymbol() == 'K' && turn_ == 'W'){
    WKingLoc_[0] = start_square[0];
    WKingLoc_[1] = start_square[1];
  }

  if(piece_to_move->getSymbol() == 'K' && turn_ == 'B'){
    BKingLoc_[0] = start_square[0];
    BKingLoc_[1] = start_square[1];
  }
  board_[end_square[0]][end_square[1]] = move_to_square;
  board_[start_square[0]][start_square[1]] = piece_to_move;

}


err ChessBoard::checkCheck(piece_ptr piece_to_move,piece_ptr move_to_square,
			   int start_square[2],int end_square[2],bool complete_move){

  if(piece_to_move->getSymbol() == 'K' && turn_ == 'W'){
    WKingLoc_[0] = end_square[0];
    WKingLoc_[1] = end_square[1];
  }

  if(piece_to_move->getSymbol() == 'K' && turn_ == 'B'){
    BKingLoc_[0] = end_square[0];
    BKingLoc_[1] = end_square[1];
  }

  if(turn_ == 'W'){
    if(attackingSquare('B',WKingLoc_)){
      reset_move(piece_to_move,move_to_square,start_square,end_square);
      if(WCheck)return MoveKOutCheck;
      if(!WCheck)return KIntoCheck;
    }

    if(attackingSquare('W',BKingLoc_) && complete_move){
      return BInCheck;
    }
  }

  if(turn_ == 'B'){

    if(attackingSquare('W',BKingLoc_)){
      reset_move(piece_to_move,move_to_square,start_square,end_square);
      if(BCheck) return MoveKOutCheck;
      if(!BCheck)return KIntoCheck;
    }
    if(attackingSquare('B',WKingLoc_) && complete_move){
      return WInCheck;
    }
  }
  return NoError;
}


void ChessBoard:: printMessage(err code, const string start, const string end){


  if(code ==NoError || code <KIntoCheck){
    cout << moved_piece_->getColourStr() << "'s "
	 << moved_piece_->getPieceStr() << " moves from " << start << " to " << end;
    if(taken_piece_ != NULL){
      cout << " taking " << taken_piece_->getColourStr() << "'s " << taken_piece_->getPieceStr();
    }
    cout << endl;
  }
  
  switch(code){
  case 0:
    if(turn_ == 'B') BCheck = false;
    if(turn_ == 'W') WCheck = false;
    changeTurn();
    break;
  case GameOver:
    cout << "Game Over";
    break;
  case IncorrectStartSquare:
    std::cerr << start << "is not a valid square\n";
    break;
  case IncorrectEndSquare:
    std::cerr << end << "is not a valid square\n";
    break;
  case StSqOutBoard:
    std::cerr << start << "is not a valid square\n";
    break;
  case ESqOutBoard:
    std::cerr << end << "is not a valid square\n";
    break;
  case SameSqr:
    std::cerr << "Your move starts and ends on the same square " << end << std::endl;
    break;
  case NoPiece:
    std::cerr << "No piece to move at square : " << start << std::endl;
    break;
  case TakeKing:
    std::cerr << "You can't take a king! On square : " << end << std::endl;
    break;
  case TakeSameCol:
    std::cerr << "You can't take your own piece! On square : " << end << std::endl;
    break;
  case InvalidMove:
    std::cerr << "Invalid move for piece of type " << moved_piece_->getPieceStr() << " from:" <<
      start <<  " to " << end <<  std::endl;
    break;
  case BlockPiece:
    std::cerr << "There is a piece blocking the move from : "
	      << start << " to : " << end <<std::endl;
    break;
  case MoveKOutCheck:
    std::cerr << "You must move your King out of check!! " << std::endl;
    break;
  case KIntoCheck:
    std::cerr << "You can't put your King into check!! " << std::endl;
    break;
  case BInCheck:
    BCheck = true;
    WCheck = false;
    cout << "Black is in check\n";
    changeTurn();
    break;
  case WInCheck:
    WCheck = true;
    BCheck = false;
    cout << "White is in check\n";
    changeTurn();
    break;
  case StaleMate:
    cout << "Stalemate: it is a draw\n";
    gameOver_ = true;
    break;
  case WChMate:
    cout << "White is in checkmate\n";
    gameOver_ = true;
    break;
  case BChMate:
    cout << "Black is in checkmate\n";
    gameOver_ = true;
    break;
  }
}

