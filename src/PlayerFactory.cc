#include "PlayerFactory.hh"

Player* PlayerFactory::build(PlayerType playerType, OwnerType owner){
    switch (playerType)
    {
    case EASY:
        return new PlayerEasy(owner);       
    case MEDIUM:
        return new PlayerMid(owner);
    case MINIMAX:
        return new PlayerMiniMax(owner);
    case ALFABETA_PRUNING:
        return new PlayerAlfaBeta(owner);
    case HUMAN:
        return new PlayerHuman(owner);
    }
}

