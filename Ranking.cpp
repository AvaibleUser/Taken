#include <iostream>
#include "Ranking.h"


using namespace std;

Ranking::Ranking(Player *player) {
    root = player;
}

Ranking::Ranking(Player *player, const size_t &pos, Ranking *dad) {
    rank = pos;
    root = player;
    father = dad;
}

Ranking::~Ranking() {
    delete root;
    delete leftLeaf;
    delete rightLeaf;
}

size_t Ranking::insert(Player *player) {
    if (player->score < root->score) {
        return simpleLeftInsert(player);
    } else if (player->score > root->score) {
        return simpleRightInsert(player);
    } else {
        if (player->gameTime > root->gameTime) {
            return simpleLeftInsert(player);
        } else {
            return simpleRightInsert(player);
        }
    }
}

size_t Ranking::simpleLeftInsert(Player *player) {
    size_t playerRank;
    if (leftLeaf == nullptr) {
        leftLeaf = new Ranking(player, rank + 1, this);
        playerRank = rank + 1;
    } else {
        playerRank = leftLeaf->insert(player);
        if (isBalanced() < -1) {
            if (leftLeaf->isBalanced() > 0) {
                leftLeaf->leftRotation();
            }
            rightRotation();
        }
    }
    return playerRank;
}

size_t Ranking::simpleRightInsert(Player *player) {
    size_t playerRank;
    if (rightLeaf == nullptr) {
        rightLeaf = new Ranking(player, rank, this);
        playerRank = rank;
    } else {
        playerRank = rightLeaf->insert(player);
        if (isBalanced() > 1) {
            if (rightLeaf->isBalanced() < 0) {
                rightLeaf->rightRotation();
            }
            leftRotation();
        }
    }
    rank++;
    return playerRank;
}

void Ranking::print() const {
    if (rightLeaf != nullptr) {
        rightLeaf->print();
    }
    cout << "\n" << rank << ". | " << root->name << " | " << root->steps << " pasos | ";
    cout << root->score << " pts | " << root->gameTime << " seg";
    if (leftLeaf != nullptr) {
        leftLeaf->print();
    }
}

int Ranking::getLevel() const {
    int levelLeft = 0;
    int levelRight = 0;

    if (leftLeaf != nullptr) {
        levelLeft = leftLeaf->getLevel();
    }
    if (rightLeaf != nullptr) {
        levelRight = rightLeaf->getLevel();
    }
    if (levelLeft < levelRight) {
        return levelRight + 1;
    } else {
        return levelLeft + 1;
    }
}

int Ranking::isBalanced() const {
    int levelLeft = 0;
    int levelRight = 0;

    if (leftLeaf != nullptr) {
        levelLeft = leftLeaf->getLevel();
    }
    if (rightLeaf != nullptr) {
        levelRight = rightLeaf->getLevel();
    }
    return levelRight - levelLeft;
}

void Ranking::leftRotation() {
    if (father != nullptr) {
        if (father->rightLeaf == this)
            father->rightLeaf = rightLeaf;
        else if (father->leftLeaf == this)
            father->leftLeaf = rightLeaf;
    }
    Ranking *tmp = rightLeaf;
    tmp->father = father;
    rightLeaf = tmp->leftLeaf;
    tmp->leftLeaf = this;
    father = tmp;
}

void Ranking::rightRotation() {
    if (father != nullptr) {
        if (father->rightLeaf == this)
            father->rightLeaf = leftLeaf;
        else if (father->leftLeaf == this)
            father->leftLeaf = leftLeaf;
    }
    Ranking *tmp = leftLeaf;
    tmp->father = father;
    leftLeaf = tmp->rightLeaf;
    tmp->rightLeaf = this;
    father = tmp;
}

Ranking *Ranking::getRoot() {
    if (father == nullptr)
        return this;
    return father->getRoot();
}
