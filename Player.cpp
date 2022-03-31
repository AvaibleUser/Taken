#include <string>
#include <chrono>
#include "Player.h"

Player::Player(const std::string &na, const size_t &st, const double &gt, const size_t &sc) {
    name = na;
    steps = st;
    score = sc;
    gameTime = gt;
}
