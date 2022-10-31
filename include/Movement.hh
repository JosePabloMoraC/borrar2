#ifndef MOVEMENT_HH
#define MOVEMENT_HH

#include "Board.hh"
/*TODO: Revisar necesidad de EMPTY*/
enum Directions { WEST, EAST, NORTH, SOUTH, EMPTY };

// Clase "Jugada".
class Movement {
private:
  // xPos y yPos son indices en la matriz
  int xPos, yPos;
  Directions lineDirection;
  bool valid;

public:
  Movement(int xPos, int yPos, enum Directions lineDirection);
  Movement(bool valid);
  ~Movement();
  int getXPos();
  int getYPos();
  Directions getLineDirection();
  // Juega esa jugada en el tablero.
  OwnerType playAndAssignOwner(Board &currentBoard, enum OwnerType owner);
  // Es una jugada dentro del tamaño del board::boxes?
  // No es una jugada repetida?
  bool isValid();
};

#endif