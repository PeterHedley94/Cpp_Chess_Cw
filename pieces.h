#ifndef PIECES_H
#define PIECES_H

#include <string>

class Piece;
typedef Piece* piece_ptr;
enum direction{UP = 1, DOWN = -1};

class Piece{
 protected:
  char symbol_;
  char colour_;
  int start_location_[2];
  int dist_travel_;
  direction dir_;
  std::string col_str_;
  std::string type_str_;

 public:
 virtual ~Piece(){}
 Piece(std::string type_str,char symbol, int m, int n, int dist_travel);
 char getColour(){return colour_;}
 char getSymbol(){ return symbol_;}
 std::string getColourStr(){return col_str_;}
 std::string getPieceStr(){return type_str_;}
 virtual bool move(int routeUp[],int routeAcross[],bool take)=0;
};

class Pawn :public Piece{
 public:
  Pawn(int m, int n);
  bool move(int routeUp[],int routeAcross[],bool take);
};

class Rook: public Piece{
  bool has_moved_;
 public:
  Rook(int m, int n);
  bool move(int routeUp[],int routeAcross[],bool take);
};


class Knight : public Piece{
 public:
  Knight(int m, int n);
  bool move(int routeUp[],int routeAcross[],bool take);
};


class Bishop :public Piece{
 public:
  Bishop(int m, int n);
  bool move(int routeUp[],int routeAcross[],bool take);
};


class Queen :public Piece{
 public:
  Queen(int m, int n);
  bool move(int routeUp[],int routeAcross[],bool take);
};


class King :public Piece{
  bool has_moved_;
 public:
  King(int m, int n);
  bool move(int routeUp[],int routeAcross[],bool take);
};


bool vertMove(direction dir,int dist_travel,int routeUp[],int routeAcross[]);
bool diagMove(direction dir,int dist_travel,int routeUp[],int routeAcross[]);
bool sideMove(int dist_travel,int routeUp[],int routeAcross[]);

#endif
