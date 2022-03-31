#ifndef TAKEN_GAMEMANAGER_H
#define TAKEN_GAMEMANAGER_H


#include <string>
#include <chrono>
#include "Matrix.h"
#include "MatrixBuilder.h"
#include "Ranking.h"


class GameManager {
private:
    Matrix *matrix = nullptr;

    Ranking *ranking = nullptr;

    MatrixBuilder *builder = nullptr;

    const std::string msgMoves = "\n\n¿Que pieza quiere mover al espacio vacio?:\n";

    const std::string msgOption = "\n\t\tOpcion:\t";

    bool requestUserMove();

    bool requestGameOption();

    void initGame();

public:
     ~GameManager();

     void manageGame();
};


#endif //TAKEN_GAMEMANAGER_H
