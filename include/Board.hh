#ifndef BOARD_HH
#define BOARD_HH

#include "Cell.hh"
#include "Movement.hh"
#include <vector>

class Board {
private:
    // matriz
    vector<vector<Cell>> boxes;
    int player1Score, player2Score;

public:
    // los size son el numero de columnas o filas de puntos.
    Board(int rowSize, int colSize);
    ~Board();
    void increaseScore(enum OwnerType player,
        int diff);
    int getScoreP1();
    int getScoreP2();
    // Cantidad de filas y columnas.
    int getBoardRowSize();
    int getBoardColSize();
    // xPos y yPos son indices en el tablero.
    Cell* getCell(int xPos, int yPos);
    // jugadas disponibles.
    vector<Movement> getAvailableMoves();
};

#endif