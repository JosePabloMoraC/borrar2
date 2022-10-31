#include "MiniMax.hh"

MiniMax::MiniMax(Board board, bool isMaxPlayer, int depth)
    : myBoard(board),
    maxPlayer(isMaxPlayer),
    myDepth(depth),
    bestMove(-1, -1, EMPTY),
    initialDepth(depth) {
    availableMoves = myBoard.getAvailableMoves();
}

MiniMax::MiniMax(Board board, bool isMaxPlayer, int depth, int initialDepth)
    : myBoard(board),
    maxPlayer(isMaxPlayer),
    myDepth(depth),
    bestMove(-1, -1, EMPTY),
    initialDepth(initialDepth) {
    availableMoves = myBoard.getAvailableMoves();
}

MiniMax::~MiniMax() {}

short MiniMax::performMiniMax(enum OwnerType max_player, enum OwnerType min_player) {
    short remainingMoves = availableMoves.size();

  // Devuelva el valor heuristico
    if (myDepth == 0 || remainingMoves == 0) {
        short totalSquares = myBoard.getBoardRowSize() * myBoard.getBoardColSize();
        short scoreP1 = myBoard.getScoreP1();
        short scoreP2 = myBoard.getScoreP2();
        short deltaScore = PLAYER1 == max_player ? scoreP1 * 2 - scoreP2 * 3 : scoreP2 * 2 - scoreP1 * 3;
        return deltaScore + totalSquares - scoreP1 - scoreP2;
    }

    short score;
    // Si el jugador es max
    if (maxPlayer) {
        score = -1000;
        for (int i = 0; i < remainingMoves; i++) {
            // Creamos un nuevo tablero para no modificar el "original".
            Board currentBoard = myBoard;
            Movement* currentMove = &availableMoves[i];
            short childScore = -1000;
            // Si al jugar, se complet� una celda entonces el jugador 1 tiene un turno extra.
            OwnerType result = currentMove->playAndAssignOwner(currentBoard, max_player);
            MiniMax childMiniMax(currentBoard, result == max_player, myDepth - 1, initialDepth);

            childScore = childMiniMax.performMiniMax(max_player, min_player);

            if (childScore > score) {
                score = childScore;
                setBestMove(*currentMove);
            }
        }
        // Si el jugador es mini
    }
    else {
        score = 1000;
        for (int i = 0; i < remainingMoves; i++) {
            Board currentBoard = myBoard;
            Movement* currentMove = &availableMoves[i];

            short childScore = 1000;
            // Si al jugar, se complet� una celda entonces el jugador 2 tiene un turno extra.
            OwnerType result =  currentMove->playAndAssignOwner(currentBoard, min_player);

            MiniMax childMiniMax(currentBoard, result != min_player, myDepth - 1, initialDepth);
            childScore = childMiniMax.performMiniMax(max_player, min_player);

            if (childScore < score) {
                score = childScore;
                setBestMove(*currentMove);
            }
        }
    }
    return score;
}

short MiniMax::performAlfaBeta(enum OwnerType max_player, enum OwnerType min_player, short alfa, short beta) {
    short remainingMoves = availableMoves.size();

    // Devuelva el valor heuristico
    if (myDepth == 0 || remainingMoves == 0) {
        short totalSquares = myBoard.getBoardRowSize() * myBoard.getBoardColSize();
        short scoreP1 = myBoard.getScoreP1();
        short scoreP2 = myBoard.getScoreP2();
        short deltaScore = PLAYER1 == max_player ? scoreP1 * 2 - scoreP2 * 3 : scoreP2 * 2 - scoreP1 * 3;
        return deltaScore + totalSquares - scoreP1 - scoreP2;
    }

    short score;
    // Si el jugador es max
    if (maxPlayer) {
        score = -1000;
        for (int i = 0; i < remainingMoves; i++)
        {
            Board currentBoard = myBoard;
            Movement* currentMove = &availableMoves[i];
            short childScore = -1000;

            OwnerType result = currentMove->playAndAssignOwner(currentBoard, max_player);

            MiniMax childMiniMax(currentBoard, result == max_player, myDepth - 1, initialDepth);
            childScore = childMiniMax.performAlfaBeta(max_player, min_player, alfa, beta);

            if (childScore > score ) {
                score = childScore;
                setBestMove(*currentMove); 
            }
            // Si score es mayor que alfa, actualizamos el valor. 
            if (score > alfa) {
                alfa = score;
            }
            
            if (score >= beta) {
                break; 
            }
        }
    }
    // Si el jugador es Min. 
    else {
        score = 1000;
        for (int i = 0; i < remainingMoves; i++)
        {
            Board currentBoard = myBoard;
            Movement* currentMove = &availableMoves[i];

            short childScore = 1000;

            OwnerType result = currentMove->playAndAssignOwner(currentBoard, min_player);

            MiniMax childMiniMax(currentBoard, result != min_player, myDepth - 1, initialDepth);
            childScore = childMiniMax.performAlfaBeta(max_player, min_player, alfa, beta);

            if (childScore < score) {
                score = childScore;
                setBestMove(*currentMove);
            }
            // Si score es menor que beta, actualizamos el valor. 
            if (score < beta) {
                beta = score;
            }

            if (score <= alfa) {
                break;
            }

        }
    }
    return score;
}

void MiniMax::setBestMove(Movement move) {
    bestMove = move;
}


Movement MiniMax::getBestMove() {
    return bestMove;
}