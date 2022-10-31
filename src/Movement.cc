#include "Movement.hh"

Movement::Movement(int xPos, int yPos, Directions lineDirection)
    : xPos(xPos), yPos(yPos), lineDirection(lineDirection), valid(true) {}

Movement::Movement(bool valid) : valid(valid) {}

Movement::~Movement() {}

int Movement::getXPos() { return xPos; }

int Movement::getYPos() { return yPos; }

Directions Movement::getLineDirection() { return lineDirection; }

bool Movement::isValid() { return valid; }
// Metodo "Jugar":
/*
Función creada a la medida de MiniMax. Se encarga de realizar la jugada y en
caso de que se complete la celda devuelve el dueño de la esta. */
OwnerType Movement::playAndAssignOwner(Board &currentBoard,
                                       enum OwnerType owner) {
  Cell *currentCell = currentBoard.getCell(xPos, yPos);
  if (!currentCell) {
    return NO_VALID;
  }
  int completed = 0;
  switch (lineDirection) {
  case WEST:
    if (currentCell->west != NO_OWNER) {
      return NO_VALID;
    }
    currentCell->west = owner;
    completed += currentCell->boxChecker(owner) ? 1 : 0;
    if (yPos > 0) {
      currentBoard.getCell(xPos, yPos - 1)->east = owner;
      completed +=
          currentBoard.getCell(xPos, yPos - 1)->boxChecker(owner) ? 1 : 0;
    }
    break;
  case EAST:
    if (currentCell->east != NO_OWNER) {
      return NO_VALID;
    }
    currentCell->east = owner;
    completed += currentCell->boxChecker(owner) ? 1 : 0;
    if (yPos + 1 < currentBoard.getBoardColSize()) {
      currentBoard.getCell(xPos, yPos + 1)->west = owner;
      completed +=
          currentBoard.getCell(xPos, yPos + 1)->boxChecker(owner) ? 1 : 0;
    }
    break;
  case NORTH:
    if (currentCell->north != NO_OWNER) {
      return NO_VALID;
    }
    currentCell->north = owner;
    completed += currentCell->boxChecker(owner) ? 1 : 0;
    if (xPos > 0) {
      currentBoard.getCell(xPos - 1, yPos)->south = owner;
      completed +=
          currentBoard.getCell(xPos - 1, yPos)->boxChecker(owner) ? 1 : 0;
    }
    break;
  case SOUTH:
    if (currentCell->south != NO_OWNER) {
      return NO_VALID;
    }
    currentCell->south = owner;
    completed += currentCell->boxChecker(owner) ? 1 : 0;

    if (xPos < currentBoard.getBoardRowSize() - 1) {
      currentBoard.getCell(xPos + 1, yPos)->north = owner;
      completed +=
          currentBoard.getCell(xPos + 1, yPos)->boxChecker(owner) ? 1 : 0;
    }
    break;

  default:
    return NO_OWNER;
  }
  if (completed > 0) {
    // suma de cajas
    currentBoard.increaseScore(owner, completed);
    return owner;
  }
  return NO_OWNER;
}