#include "Board.hh"

Board::Board(int rowSize, int colSize) : player1Score(0), player2Score(0) {
    // size-1 pues, por una matriz de n*m puntos, hay (n-1)*(m-1) cajas.
    // Filas
    boxes.resize(rowSize - 1);
    // Columnas
    for (int i = 0; i < rowSize - 1; i++) {
        boxes[i].resize(colSize - 1);
    }
}

Board::~Board() {
    for (int i = 0; i < boxes.size(); i++) {
        boxes[i].clear();
    }
    boxes.clear();
}

void Board::increaseScore(OwnerType player, int diff) {
    switch (player) {
    case PLAYER1:
        player1Score += diff;
        break;
    case PLAYER2:
        player2Score += diff;
        break;

    default:
        break;
    }
}

int Board::getScoreP1() { return player1Score; }

int Board::getScoreP2() { return player2Score; }

int Board::getBoardRowSize() { return boxes.size(); }

int Board::getBoardColSize() { return boxes[0].size(); }

Cell* Board::getCell(int xPos, int yPos) {
    // Revisa validez de los indices.
    if (xPos >= 0 && xPos < boxes.size() && yPos >= 0 && yPos < boxes[0].size()) {
        return &(boxes[xPos][yPos]);
    }
    return nullptr;
}

vector<Movement> Board::getAvailableMoves() {
    vector<Movement> moves;
    // Verifica todos los lados de cada celda.
    // No queremos las dos formas de hacer un mismo move.
    for (int i = 0; i < boxes.size(); i++) {
        for (int j = 0; j < boxes[i].size(); j++) {
            // E y S se colocan sin revisar pues no se tienen en un anterior.
            // W y N si se revisan pues se puede haber colocado anteriormente.
            if (boxes[i][j].east == NO_OWNER) {
                moves.push_back({ i, j, EAST });
            }
            if (j == 0 && boxes[i][j].west == NO_OWNER) {
                moves.push_back({ i, j, WEST });
            }
            if (i == 0 && boxes[i][j].north == NO_OWNER) {
                moves.push_back({ i, j, NORTH });
            }
            if (boxes[i][j].south == NO_OWNER) {
                moves.push_back({ i, j, SOUTH });
            }
        }
    }
    return moves;
}