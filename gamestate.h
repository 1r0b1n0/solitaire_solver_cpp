#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>
#include <vector>
#include <array>

#define JEU_SIZE 9

class GameState;
typedef std::shared_ptr<GameState> GameStatePtr;

class GameState
{

public:
    enum class State{
        INACCESSIBLE,
        OCCUPE,
        VIDE
    };

    GameState();
    void print();

    std::array<std::array<State, JEU_SIZE>, JEU_SIZE> m_state;
    size_t xprev = 0;
    size_t yprev = 0;

    static void solve(const GameStatePtr &statePtr, std::vector<GameStatePtr> prevStates);
};

#endif // GAMESTATE_H
