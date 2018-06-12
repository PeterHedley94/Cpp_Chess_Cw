#include <iostream>
#include "ChessBoard.h"

using namespace std;




void initialMoveCheck(ChessBoard& cb);
void checkPawnUpwardMove(ChessBoard& cb);
void checkPawnDownwardMove(ChessBoard& cb);
void checkOutOfMap(ChessBoard& cb);
void sa(ChessBoard& cb);
void testCheck(ChessBoard& cb);
void testStale(ChessBoard& cb);

int main() {

    cout << "===========================" << endl;
    cout << "Testing the Chess Engine" << endl;
    cout << "===========================" << endl;
    cout << endl;


    ChessBoard cb;
    //cb.printBoard();
    //sa(cb);
    //initialMoveCheck(cb);
    //checkPawnUpwardMove(cb);
    //checkPawnDownwardMove(cb);
    //checkOutOfMap(cb);
    //testCheck(cb);
    //testStale(cb);


    cb.submitMove("D7", "D6");
    cout << endl;


    cb.submitMove("D4", "H6");
    cout << endl;

    cb.submitMove("D2", "D4");
    cout << endl;


    cb.submitMove("F8", "B4");
    cout << endl;

    cout << "===========================" << endl;
    cout << "Alekhine vs. Vasic (1931)" << endl;
    cout << "===========================" << endl;
    cout << endl;

    cb.resetBoard();
    cout << endl;

    cb.submitMove("E2", "E4");


    cb.submitMove("E7", "E6");
    cout << endl;


    cb.submitMove("D2", "D4");
    cb.submitMove("D7", "D5");
    cout << endl;


    cb.submitMove("B1", "C3");
    cb.submitMove("F8", "B4");
    cout << endl;

    cb.submitMove("F1", "D3");
    cb.submitMove("B4", "C3");
    cout << endl;


    cb.submitMove("B2", "C3");
    cb.submitMove("H7", "H6");
    cout << endl;


    cb.submitMove("C1", "A3");

    cb.submitMove("B8", "D7");
    cout << endl;


    cb.submitMove("D1", "E2");


    cb.submitMove("D5", "E4");
    cout << endl;

    cb.submitMove("D3", "E4");

    cb.submitMove("G8", "F6");
    cout << endl;

    cb.submitMove("E4", "D3");
    cb.submitMove("B7", "B6");
    cout << endl;


    cb.submitMove("E2", "E6");
    cb.submitMove("F7", "E6");
    cout << endl;

    cb.submitMove("D3", "G6");
    cout << endl;

    return 0;
}


//#******************************************************

void sa(ChessBoard& cb){
  char temp_board[8][8] = {'B'};
  for(int m=0; m<8;m++){
    for(int n=0; n<8; n++){
      int sq[2] = {m,n};
      /*
      for(int t=0; t<2;t++){
	cout << "......." << sq[t];
	}*/
      char W  = 'W';
      char B = 'B';
      if(cb.attackingSquare(W,sq)){
	//cout << "m is : " << m << " n is : " << n << endl;
	temp_board[m][n] = 'W';
	//}else if(cb.attackingSquare(sq,W)){
	//temp_board[m][n] == 'B';
      }else{
	temp_board[m][n] = ' ';
      }
    }
  }


  char boardLetters[9] = "ABCDEFGH";
  cout << endl <<  "     ";

  for(int m=0; m<8; m++)
    cout << boardLetters[m] << "    ";
  cout << endl <<  "    ";
  for(int n=0; n<8; n++)
    cout << "-----";
  cout << endl;
  for(int m=0; m<8; m++){
    cout << " " << 8-m << " | ";
    for(int n=0; n<8; n++){
      cout << " " << temp_board[m][n] << "  |";
    }
    cout << " " << 8-m << endl << "    ";
    for(int n=0; n<8; n++)
      cout << "-----";
    cout << endl;
  }
  cout <<  "     ";
  for(int m=0; m<8; m++)
    cout << boardLetters[m] << "    ";
  cout << endl << endl;

}

void testCheck(ChessBoard& cb){
  cb.submitMove("E8","D8");
  cb.submitMove("E8","F8");
  cb.submitMove("D1","D5");
  cb.submitMove("E7","E6");
  cb.submitMove("D5","C5");
  //sa(cb);
  /*
  BKingLoc_[0] = 0;
  BKingLoc_[1] = 4;
  WKingLoc_[0] = 7;
  WKingLoc_[1] = 4;*/
}

void testStale(ChessBoard& cb){

    /*
  board_[0][4] = new King(0,4);
  board_[1][4] = new Pawn(1,4);
  board_[6][4] = new Pawn(6,4);
  board_[7][3] = new Queen(7,3);
  board_[7][4] = new King(7,4);
  board_[7][7] = new Rook(7,7);*/

  cb.submitMove("E8","F8");
  sa(cb);

  cb.submitMove("H1","F1");
  sa(cb);
  cout << "Start of incorrect Pawn Move \n";
  cb.submitMove("E7","E6");
  cout << "End of incorrect Pawn move \n";
  cb.submitMove("F8","E8");
  sa(cb);
  cb.submitMove("F1","G1");
  cb.submitMove("E8","F8");

  cb.submitMove("E2","E3");
  cb.submitMove("F8","E8");
  cb.submitMove("E3","E4");
  cb.submitMove("E8","F8");
  cb.submitMove("E4","E5");
  cb.submitMove("F8","E8");
  cb.submitMove("E5","E6");
  cb.submitMove("E8","F8");
  cb.submitMove("G1","F1");
  cb.submitMove("F8","E8");
  /*
  cb.submitMove("D1","E2");
  cb.submitMove("E7","E6");
  //cb.submitMove("E8","E9"); // did cause a check problem?
  cb.submitMove("D5","D6");*/

}


void checkOutOfMap(ChessBoard& cb){

  cb.submitMove("7", "D2");
  cb.submitMove("D7", "6");
  cb.submitMove("d7", "D2");
  cb.submitMove("D7", "d6");
  cb.submitMove("I7", "D6");
  cb.submitMove("D7", "D9");
  cb.submitMove("D0", "D6");
  cb.submitMove("D7", "D0");
  cb.submitMove("D9", "D6");
  cb.submitMove("D7", "Z6");
  cb.submitMove("I7", "Z6");
  cb.submitMove("D!", "Z6");
  cb.submitMove("D7", "!6");
  cb.submitMove(".7", "Z6");
  cb.submitMove("", "D6");
  cb.submitMove("D72", "Z6");
  cb.submitMove("D7", "D62");
  cb.submitMove("D7", "");
  cb.submitMove("D7", "Z6");
}

void initialMoveCheck(ChessBoard& cb){
  cb.submitMove("D2","D2");
  cb.submitMove("D1","D8");
  cb.submitMove("D1","E1");
}

void checkPawnUpwardMove(ChessBoard& cb){
  cb.submitMove("A2","A4");
  cb.submitMove("B2","B3");
  cb.submitMove("B3","B4");
  cb.submitMove("B4","B6");
  cb.submitMove("C2","C5");
  cb.submitMove("D2","E3");
  cb.submitMove("D2","E2");
  cb.submitMove("D2","D1");
  cb.submitMove("D2","H1");
}

void checkPawnDownwardMove(ChessBoard& cb){
  cb.submitMove("A7","A6");
  cb.submitMove("B7","B5");
  cb.submitMove("B5","B4");
  cb.submitMove("B5","A4");
  cb.submitMove("A6","A5");
  cb.submitMove("A5","B4");
  cb.submitMove("E7","E6");
  cb.submitMove("E6","E4");
  cb.submitMove("E6","E7");
  cb.submitMove("C7","C4");
  cb.submitMove("D7","E7");
  cb.submitMove("D7","E6");
  cb.submitMove("D7","D8");
  cb.submitMove("D7","H8");
}
