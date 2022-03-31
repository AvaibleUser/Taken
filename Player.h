#ifndef TAKEN_PLAYER_H
#define TAKEN_PLAYER_H


#include <string>
#include <chrono>


struct Player {
public:
    std::string name;
    size_t steps;
    double gameTime;
    size_t score;

    Player(const std::string &na, const size_t &st, const double &gt, const size_t &sc);
};


#endif //TAKEN_PLAYER_H
