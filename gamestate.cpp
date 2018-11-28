#include "gamestate.h"
#include <stdio.h>
#include <iostream>

/*
000000000
000XXX000
000XXX000
0XXXXXXX0
0XXXOXXX0
0XXXXXXX0
000XXX000
000XXX000
000000000
*/

GameState::GameState()
{
    for(size_t x=0;x<JEU_SIZE;x++)
    {
        for(size_t y=0;y<JEU_SIZE;y++)
        {
            m_state[x][y] = State::INACCESSIBLE;
        }
    }
    m_state[3][1] = State::OCCUPE;
    m_state[4][1] = State::OCCUPE;
    m_state[5][1] = State::OCCUPE;
    m_state[3][2] = State::OCCUPE;
    m_state[4][2] = State::OCCUPE;
    m_state[5][2] = State::OCCUPE;

    m_state[1][3] = State::OCCUPE;
    m_state[2][3] = State::OCCUPE;
    m_state[3][3] = State::OCCUPE;
    m_state[4][3] = State::OCCUPE;
    m_state[5][3] = State::OCCUPE;
    m_state[6][3] = State::OCCUPE;
    m_state[7][3] = State::OCCUPE;
    m_state[1][4] = State::OCCUPE;
    m_state[2][4] = State::OCCUPE;
    m_state[3][4] = State::OCCUPE;
    m_state[4][4] = State::VIDE;
    m_state[5][4] = State::OCCUPE;
    m_state[6][4] = State::OCCUPE;
    m_state[7][4] = State::OCCUPE;
    m_state[1][5] = State::OCCUPE;
    m_state[2][5] = State::OCCUPE;
    m_state[3][5] = State::OCCUPE;
    m_state[4][5] = State::OCCUPE;
    m_state[5][5] = State::OCCUPE;
    m_state[6][5] = State::OCCUPE;
    m_state[7][5] = State::OCCUPE;

    m_state[3][6] = State::OCCUPE;
    m_state[4][6] = State::OCCUPE;
    m_state[5][6] = State::OCCUPE;
    m_state[3][7] = State::OCCUPE;
    m_state[4][7] = State::OCCUPE;
    m_state[5][7] = State::OCCUPE;
}

void GameState::print()
{
    for(size_t x=0;x<JEU_SIZE;x++)
    {
        for(size_t y=0;y<JEU_SIZE;y++)
        {
            auto st = m_state[x][y];
            if(st == State::INACCESSIBLE)
                std::cout << ' ';
            else if(st == State::OCCUPE)
                if(x == xprev && y==yprev)
                    std::cout << "\033[1;36m" << 'X' << "\033[0m";
                else
                    std::cout << "\033[1;31m" << 'X' << "\033[0m";
            else if(st == State::VIDE)
                std::cout << 'O';
        }
        std::cout << std::endl;
    }
}

void GameState::solve(const GameStatePtr &statePtr, std::vector<GameStatePtr> prevStates)
{
    GameState &state = *statePtr;

    int nbLeft = 0;
    for(int x=1;x<JEU_SIZE-1;x++)
    {
        for(int y=1;y<JEU_SIZE-1;y++)
        {
            if(state.m_state[x][y] == State::OCCUPE)
            {
                nbLeft++;
            }
        }
    }
    if(nbLeft == 1)
    {
        static int solutions = 0;
        solutions++;
        std::cout << "Finished ! " << solutions << std::endl;

        /*

        int cpt = 0;
        for(const auto &pst : prevStates )
        {
            cpt++;
            std::cout << "State : " << cpt << std::endl;
            pst->print();
        }

        std::cout << "\n\n" << std::endl;

        exit(0);
        */
    }

    for(size_t x=1;x<JEU_SIZE-1;x++)
    {
        for(size_t y=1;y<JEU_SIZE-1;y++)
        {
            if(state.m_state[x][y] == State::OCCUPE)
            {
                if(state.m_state[x+1][y] == State::OCCUPE && state.m_state[x+2][y] == State::VIDE)
                {
                    GameStatePtr newState = std::make_shared<GameState>(state);
                    newState->m_state[x][y] = State::VIDE;
                    newState->m_state[x+1][y] = State::VIDE;
                    newState->m_state[x+2][y] = State::OCCUPE;
                    newState->xprev = x+2;
                    newState->yprev = y;
                    auto newStates = prevStates;
                    newStates.push_back(newState);
                    solve(newState, newStates);
                }
                if(state.m_state[x-1][y] == State::OCCUPE && state.m_state[x-2][y] == State::VIDE)
                {
                    GameStatePtr newState = std::make_shared<GameState>(state);
                    newState->m_state[x][y] = State::VIDE;
                    newState->m_state[x-1][y] = State::VIDE;
                    newState->m_state[x-2][y] = State::OCCUPE;
                    newState->xprev = x-2;
                    newState->yprev = y;
                    auto newStates = prevStates;
                    newStates.push_back(newState);
                    solve(newState, newStates);
                }
                if(state.m_state[x][y+1] == State::OCCUPE && state.m_state[x][y+2] == State::VIDE)
                {
                    GameStatePtr newState = std::make_shared<GameState>(state);
                    newState->m_state[x][y] = State::VIDE;
                    newState->m_state[x][y+1] = State::VIDE;
                    newState->m_state[x][y+2] = State::OCCUPE;
                    newState->xprev = x;
                    newState->yprev = y+2;
                    auto newStates = prevStates;
                    newStates.push_back(newState);
                    solve(newState, newStates);
                }
                if(state.m_state[x][y-1] == State::OCCUPE && state.m_state[x][y-2] == State::VIDE)
                {
                    GameStatePtr newState = std::make_shared<GameState>(state);
                    newState->m_state[x][y] = State::VIDE;
                    newState->m_state[x][y-1] = State::VIDE;
                    newState->m_state[x][y-2] = State::OCCUPE;
                    newState->xprev = x;
                    newState->yprev = y-2;
                    auto newStates = prevStates;
                    newStates.push_back(newState);
                    solve(newState, newStates);
                }
            }
        }
    }
}

