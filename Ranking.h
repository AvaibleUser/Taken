//
// Created by dylan on 29/03/2022.
//

#ifndef TAKEN_RANKING_H
#define TAKEN_RANKING_H


#include "Player.h"

struct Ranking {
private:
    size_t rank = 1;
    Player *root;
    Ranking *leftLeaf = nullptr;
    Ranking *rightLeaf = nullptr;
    Ranking *father = nullptr;

    int isBalanced() const;

    int getLevel() const;

    void rightRotation();

    void leftRotation();

    size_t simpleLeftInsert(Player *player);

    size_t simpleRightInsert(Player *player);

public:
    explicit Ranking(Player *player);
    Ranking(Player *player, const size_t &rank, Ranking *dad);

    ~Ranking();

    size_t insert(Player *player);

    void print() const;

    Ranking *getRoot();
};


#endif //TAKEN_RANKING_H
