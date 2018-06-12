#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "pieces.h"
#include <string>

enum err {NoError = 0,GameOver = -1,IncorrectStartSquare=-2,IncorrectEndSquare=-3,
	  StSqOutBoard = -4, ESqOutBoard = -5,SameSqr = -6,
	  NoPiece = -7,TakeKing = -8,TakeSameCol = -9,
	  InvalidMove=-10,BlockPiece = -11,MoveKOutCheck = -12,KIntoCheck = -13,
	  BInCheck = -14, WInCheck = -15,StaleMate = -16,WChMate = -17,BChMate = -18};

using namespace std;

class ChessBoard{
  piece_ptr board_[8][8];
  piece_ptr moved_piece_;
  piece_ptr taken_piece_;
  int routeUp_[9];
  int routeAcross_[9];
  int WKingLoc_[2];
  int BKingLoc_[2];
  char turn_;
  bool BCheck;
  bool WCheck;
  bool gameOver_;

  //Checks for a Blocking Piece
  bool checkRoute() const;
  //Check Input is in correct format
  err checkInput(const string start,const string end);
  err checkInBoard() const;
  void clearBoard();
  
 public:
  ChessBoard();
  ~ChessBoard();
  void populateBoard();
  int submitMove(const string start, const string end);
  err InitiateMove(bool complete_move);
  //Check if a square can be attacked by a certain colour
  bool attackingSquare(const char colour, int sq[2]);
  void changeTurn();
  //If not pieces of a colour can make a legal move that colour is in stale mate
  bool checkStale(char colour);
  void reset_move(piece_ptr piece_to_move,piece_ptr move_to_square,
		  int start_square[2],int end_square[2]);
  err checkCheck(piece_ptr piece_to_move,piece_ptr move_to_square,
		 int start_square[2],int end_square[2],bool complete_move);

  void resetBoard(){
    clearBoard();
    populateBoard();
  }
  void printMessage(err code, const string start, const string end);
};



#endif
