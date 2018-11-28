#include <gamestate.h>
#include <iostream>

int main(int argc, char *argv[])
{
    GameStatePtr st = std::make_shared<GameState>();
    st->print();

    std::cout << "solving" << std::endl;

    GameState::solve(st, {});
}
