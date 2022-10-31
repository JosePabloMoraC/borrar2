#include "Player.hh"
#include <cstdlib>

Movement Player::randomPlay(Board &board) {
  vector<Movement> availableMoves = board.getAvailableMoves();
  // Numero al azar de 0 a n-1
  int randNum = (rand() % (availableMoves.size()));
  return availableMoves[randNum];
}

Movement PlayerEasy::rehearsedPlay(Board &board) { return randomPlay(board); }

Movement PlayerMid::rehearsedPlay(Board &board) {
  vector<Movement> tripleOptionMoves;
  vector<Movement> everyOptionMoves;
  vector<Movement> availableMoves = board.getAvailableMoves();

  for (int i = 0; i < availableMoves.size(); i++) {
    // 2 en la misma celda: Si usa uno de los dos pierde una caja.
    if (i + 1 < availableMoves.size() &&
        availableMoves[i].getXPos() == availableMoves[i + 1].getXPos() &&
        availableMoves[i].getYPos() == availableMoves[i + 1].getYPos()) {
      // 3 en la misma celda:
      if (i + 2 < availableMoves.size() &&
          availableMoves[i].getXPos() == availableMoves[i + 2].getXPos() &&
          availableMoves[i].getYPos() == availableMoves[i + 2].getYPos()) {
        // 4 en la misma celda.
        if (i + 3 < availableMoves.size() &&
            availableMoves[i].getXPos() == availableMoves[i + 3].getXPos() &&
            availableMoves[i].getYPos() == availableMoves[i + 3].getYPos()) {
          everyOptionMoves.push_back(availableMoves[i]);
          everyOptionMoves.push_back(availableMoves[i + 1]);
          everyOptionMoves.push_back(availableMoves[i + 2]);
          everyOptionMoves.push_back(availableMoves[i + 3]);
          i += 3;
        } else {
          tripleOptionMoves.push_back(availableMoves[i]);
          tripleOptionMoves.push_back(availableMoves[i + 1]);
          tripleOptionMoves.push_back(availableMoves[i + 2]);
          i += 2;
        }
      }
      // Solo hay 2.
      i++;
    }
    // Solo un move disponible (forma caja).
    else {
      return availableMoves[i];
    }
  }
  // Revisar opciones.
  Movement bestMove = findBestMove(board, tripleOptionMoves);
  if (!tripleOptionMoves.empty() && bestMove.isValid()) {
    return bestMove;
  } else {
    bestMove = findBestMove(board, everyOptionMoves);
    if (!everyOptionMoves.empty() && bestMove.isValid()) {
      return bestMove;
    } else {
      return randomPlay(board);
    }
  }
}

Movement PlayerMid::findBestMove(Board &board, vector<Movement> possibleMoves) {
  for (int i = 0; i < possibleMoves.size(); i++) {
    int x = possibleMoves[i].getXPos();
    int y = possibleMoves[i].getYPos();
    switch (possibleMoves[i].getLineDirection()) {
    case WEST:
      if (y > 0 && board.getCell(x, y - 1)->availableMovesCount() > 2) {
        return possibleMoves[i];
      }
      break;
    case EAST:
      if (y < board.getBoardColSize()-1 &&
          board.getCell(x, y + 1)->availableMovesCount() > 2) {
        return possibleMoves[i];
      }
      break;
    case NORTH:
      if (x > 0 && board.getCell(x - 1, y)->availableMovesCount() > 2) {
        return possibleMoves[i];
      }
      break;
    case SOUTH:
      if (x < board.getBoardRowSize()-1 &&
          board.getCell(x + 1, y)->availableMovesCount() > 2) {
        return possibleMoves[i];
      }
      break;

    default:
      break;
    }
  }
  return Movement(false);
}

Movement PlayerMiniMax::rehearsedPlay(Board &board) {
  OwnerType max;
  OwnerType min;
  if (id == PLAYER1){
      max = PLAYER1;
      min = PLAYER2;
  } else {
      max = PLAYER2;
      min = PLAYER1;
  }

  int depth = 0;
  int nNodes = 1;
  int size = board.getAvailableMoves().size();
  while (nNodes < 5000 && size > 0)
  {
      nNodes *= size;
      size -= 1;
      depth += 1;
  }
  MiniMax minimax = {board, true, depth};
  minimax.performMiniMax(max, min);
  return minimax.getBestMove();
}

Movement PlayerAlfaBeta::rehearsedPlay(Board& board) {
    OwnerType max;
    OwnerType min;
    if (id == PLAYER1) {
        max = PLAYER1;
        min = PLAYER2;
    }
    else {
        max = PLAYER2;
        min = PLAYER1;
    }

    int depth = 0;
    int nNodes = 1;
    int size = board.getAvailableMoves().size();
    while (nNodes < 200000 && size > 0)
    {
        nNodes *= size;
        size -= 1;
        depth += 1;
    }
    MiniMax minimax = { board, true, depth };
    minimax.performAlfaBeta(max, min, -15000, 15000);
    return minimax.getBestMove();
}

Movement PlayerHuman::rehearsedPlay(Board &board) {
  return Movement{-1, -1, EMPTY};
}
