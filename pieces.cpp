#include <iostream>
#include <stdlib.h>
#include <string>
#include "pieces.h"


using namespace std;


Piece :: Piece(string type_str,char symbol,int m, int n, int dist_travel)
  : symbol_(symbol), dist_travel_(dist_travel), type_str_(type_str){

  if(m >= 6){
    colour_ = 'W';
    col_str_ = "White";
    dir_ = UP;
  }else{
    dir_ = DOWN;
    colour_ = 'B';
    col_str_ = "Black";
  }
  start_location_[0] = m;
  start_location_[1] = n;
}


//#**********************************************************************

Pawn :: Pawn(int m, int n):Piece("Pawn",'P',m,n,2){}

bool Pawn :: move(int routeUp[],int routeAcross[],bool take){
  if(routeUp[0] == start_location_[0]){
    dist_travel_ = 2;
  }else{dist_travel_ = 1;}

  if(take){
    dist_travel_ = 1;
    if(diagMove(dir_,dist_travel_,routeUp,routeAcross)){
      return true;
    }
  }else{
    //cout << "Trying the Vertical Move with distance " << dist_travel_ << endl;
    if(vertMove(dir_,dist_travel_,routeUp,routeAcross)){return true;}
  }
  return false;
}

//#**********************************************************************

Rook :: Rook(int m, int n):Piece("Rook",'R',m,n,8),has_moved_(false){}

bool Rook :: move(int routeUp[],int routeAcross[],bool take){
  if(sideMove(dist_travel_,routeUp,routeAcross)){return true;}
  if(vertMove(UP,dist_travel_,routeUp,routeAcross)){return true;}
  if(vertMove(DOWN,dist_travel_,routeUp,routeAcross)){return true;}
  return false;
}

//#**********************************************************************


Knight :: Knight(int m, int n):Piece("Knight",'H',m,n,-1){}

bool Knight :: move(int routeUp[],int routeAcross[],bool take){
  int upDist = abs(routeUp[1]-routeUp[0]);
  int acDist = abs(routeAcross[1] - routeAcross[0]);
  if(abs(acDist-upDist) == 1 && upDist + acDist == 3){
    routeAcross[2] = -1;
    routeUp[2] = -1;
    return true;
  }
  return false;
}

//#**********************************************************************


Bishop :: Bishop(int m, int n):Piece("Bishop",'B',m,n,8){}

bool Bishop :: move(int routeUp[],int routeAcross[],bool take){
  if(diagMove(UP,dist_travel_,routeUp,routeAcross)){
    return true;
  }
  if(diagMove(DOWN,dist_travel_,routeUp,routeAcross)){
    return true;
  }
  return false;
}

//#**********************************************************************

Queen :: Queen(int m, int n):Piece("Queen",'Q',m,n,8){}

bool Queen :: move(int routeUp[],int routeAcross[],bool take){
  if(vertMove(UP,dist_travel_,routeUp,routeAcross)){return true;}
  if(vertMove(DOWN,dist_travel_,routeUp,routeAcross)){return true;}
  if(diagMove(UP,dist_travel_,routeUp,routeAcross)){return true;}
  if(diagMove(DOWN,dist_travel_,routeUp,routeAcross)){return true;}
  if(sideMove(dist_travel_,routeUp,routeAcross)){return true;}
  return false;
}

//#**********************************************************************


King :: King(int m, int n):Piece("King",'K',m,n,1),has_moved_(false){}

bool King :: move(int routeUp[],int routeAcross[],bool take){
  //cout << "From : " << routeUp[0] << " , " << routeAcross[0] <<
  //"To : " << routeUp[1] << " , " << routeAcross[1]<< endl;
  if(vertMove(UP,dist_travel_,routeUp,routeAcross)){return true;}
  if(vertMove(DOWN,dist_travel_,routeUp,routeAcross)){return true;}
  if(diagMove(UP,dist_travel_,routeUp,routeAcross)){return true;}
  if(diagMove(DOWN,dist_travel_,routeUp,routeAcross)){return true;}
  if(sideMove(dist_travel_,routeUp,routeAcross)){return true;}
  return false;
}


//#**********************************************************************
//ENUM DIRECTION

bool vertMove(direction dir,int dist_travel,int routeUp[],int routeAcross[]){
  if(routeAcross[0] != routeAcross[1]) return false;
  int distance =  (routeUp[0] - routeUp[1])*dir;

  if(distance < 0 || distance > dist_travel) return false;

  for(int i=1; i<=distance+1; i++){
    if(i== distance+1){
      routeUp[i] = -1;
      routeAcross[i] = -1;
    }else{
      routeUp[i] = routeUp[0] - (i*dir);
      routeAcross[i] = routeAcross[0];
    }
  }
  return true;
}


bool sideMove(int dist_travel,int routeUp[],int routeAcross[]){
  if(routeUp[0] != routeUp[1]) return false;
  bool right = true;
  int distance =  abs(routeAcross[1] - routeAcross[0]);

  if(distance < 0 || distance > dist_travel) return false;
  if(routeAcross[0]-routeAcross[1] > 0) right = false;

  for(int i=1; i<=distance+1; i++){
    if(i== distance+1){
      routeUp[i] = -1;
      routeAcross[i] = -1;
    }else{
      routeUp[i] = routeUp[0];
      if(right) routeAcross[i] = routeAcross[0] + i;
      if(!right) routeAcross[i] = routeAcross[0] - i;
    }
  }
  return true;
}

bool diagMove(direction dir,int dist_travel,int routeUp[],int routeAcross[]){
  bool right = true;
  int distance =  (routeUp[0] - routeUp[1])*dir;

  if(distance < 0 || distance > dist_travel) return false;
  if(abs(routeAcross[0]-routeAcross[1]) != distance) return false;
  if(routeAcross[0]-routeAcross[1] > 0) right = false;

  for(int i=1; i<=distance+1; i++){
    if(i== distance+1){
      routeUp[i] = -1;
      routeAcross[i] = -1;
    }else{
      routeUp[i] = routeUp[0] - (i*dir);
      if(right) routeAcross[i] = routeAcross[0] + i;
      if(!right) routeAcross[i] = routeAcross[0] - i;
    }
  }
  return true;
}
