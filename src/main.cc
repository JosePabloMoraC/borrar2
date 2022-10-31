#include "MiniMax.hh"
#include <iostream>
#include <time.h>

using namespace std; 
int main() {

	/* para almacenar el tiempo de ejecución del código
	double time_spent = 0.0;

	clock_t begin = clock();

	Board board(3, 3);
	MiniMax minimax(board, true, 5);
	minimax.performAlfaBeta(true, -15000, 15000);
	Movement bestMove = minimax.getBestMove();

	clock_t end = clock();

	// calcula el tiempo transcurrido encontrando la diferencia (end - begin) y
	// dividiendo la diferencia por CLOCKS_PER_SEC para convertir a segundos
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	printf("The elapsed time is %f seconds", time_spent);

	cout << "The best move is \nx: " << bestMove.getXPos() << "\ny: " << bestMove.getYPos()
		<< "\nDirection: " << bestMove.getLineDirection() << endl;
	*/
    /*
	Board board = { 3,3 };
	Movement moveN = { 0,1, NORTH };
	moveN.play(board, PLAYER1);
	Movement moveS = { 0,1, SOUTH };
	moveS.play(board, PLAYER2);
	Movement moveO = { 0,1, WEST };
	moveO.play(board, PLAYER1);
	Movement moveN2 = { 1,1, NORTH };
	moveN2.play(board, PLAYER2);
	Movement moveS2 = { 1,1, SOUTH };
	moveS2.play(board, PLAYER1);
	Movement moveE = { 1,1, EAST };
	moveE.play(board, PLAYER2);


	MiniMax miniMax = { board, true, 4 };
	miniMax.performMiniMax(true);
	Movement bestMove = miniMax.getBestMove();

  
    cout << "The best move is \nx: " << bestMove.getXPos() << "\ny: " << bestMove.getYPos()
        << "\nDirection: " << bestMove.getLineDirection() << endl;
	*/ 
    return 0;
}