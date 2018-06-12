chess: ChessBoard.o ChessMain.o pieces.o
	g++ -g -Wall ChessBoard.o ChessMain.o pieces.o -o chess

ChessMain.o: ChessBoard.h
	g++ -Wall -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h pieces.h
	g++ -Wall -c ChessBoard.cpp

pieces.o : pieces.cpp pieces.h
	g++ -Wall -c pieces.cpp

clean:
	rm -r *.o chess
