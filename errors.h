#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include <string>



class errors{
 public:
  static void incorrectSquare(std::string move){
    std::cerr <<  move << "is not a valid square\n";
  }
  static void startSquareOutBoard(std::string move){
    std::cerr <<  move << "is not a valid square\n";
  }

  static void endSquareOutBoard(std::string move){
    std::cerr <<  move << "is not a valid square\n";
  }

  static void sameSquare(std::string move){
    std::cerr << "Your move starts and ends on the same square " << move << std::endl;
  }

  static void takeKing(std::string move){
    std::cerr << "You can't take a king! On square : " << move << std::endl;
  }
  
  static void noPiece(std::string move){
    std::cerr << "No piece to move at square : " << move << std::endl;
  }
  
  static void takeSameCol(std::string move){
    std::cerr << "You can't take your own piece! On square : " << move << std::endl;
  }

  static void invalidMove(std::string piece, std::string end){
    std::cerr << "Invalid move for piece of type from:" <<
      piece <<  " to " << end <<  std::endl;
  }

  static void blockPiece(std::string start,std::string end){
    std::cerr << "There is a piece blocking the move from : "
	      << start << " to : " << end <<std::endl;
  }

  static void KingInCheck(){
    std::cerr << "You can't put your King into check!! " << std::endl;
  }

  static void MoveKingOutOfCheck(){
    std::cerr << "You must move your King out of check!! " << std::endl;
  }

  
  

};

#endif
