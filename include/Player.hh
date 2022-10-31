#ifndef PLAYER_HH
#define PLAYER_HH

#include "MiniMax.hh"
//#include "GameBoardPanel.hh"



// Clase "Jugador"
class Player {
protected:
  // Para saber cual color y que posee.
  OwnerType id;

public:
  Player(OwnerType owner) : id(owner) {}
  ~Player() {}

  OwnerType getId() const { return id; }
  // Método que tendrán todos los tipos de jugador(COM) independientemente de la
  // dificultad.
  virtual Movement rehearsedPlay(Board &board) = 0;
  // Movimiento al azar disponible para todas las clases herederas.
  Movement randomPlay(Board &board);
};

class PlayerEasy : public Player {
public:
  PlayerEasy(enum OwnerType owner) : Player(owner) {}
  ~PlayerEasy() {}

  // Elegir al azar.
  Movement rehearsedPlay(Board &board);
};

class PlayerMid : public Player {
public:
  PlayerMid(enum OwnerType owner) : Player(owner) {}
  ~PlayerMid() {}

  // Busca un movimiento que no implique un mal movimiento para las celdas
  // alrededor.
  Movement findBestMove(Board &board, vector<Movement> possibleMoves);
  /*
  Busca confundir al jugador medio cerrando una caja,
  o busca la posibilidad de cerrar alguna caja, cuando
  no existe la posibilidad de hacer alguna jugada para
  acercarse al objetivo de cerrar, busca una opción
  que no afecte, si no la encuentra, elige al azar.
   */
  Movement rehearsedPlay(Board &board); // cambios del prof. , revisar validez
};

// MiniMax
class PlayerMiniMax : public Player {
public:
  PlayerMiniMax(OwnerType owner) : Player(owner) {}
  Movement rehearsedPlay(Board &board);
};

class PlayerAlfaBeta : public Player {
public:
  PlayerAlfaBeta(OwnerType owner) : Player(owner) {}
  Movement rehearsedPlay(Board &board);
};

class PlayerHuman : public Player {
public:
  PlayerHuman(OwnerType owner) : Player(owner) {}
  Movement rehearsedPlay(Board &board); //, Movement gameBoardMove
};


#endif