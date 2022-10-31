#ifndef PLAYERFACTORY_HH
#define PLAYERFACTORY_HH

#include "Player.hh"

enum PlayerType { EASY, MEDIUM, MINIMAX, ALFABETA_PRUNING, HUMAN };

class PlayerFactory {
  public: 
    Player* build (PlayerType playerType, OwnerType owner);
};

#endif