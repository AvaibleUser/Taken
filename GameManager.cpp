#include <string>
#include <iostream>
#include "GameManager.h"
#include "UtilityFunctions.h"
#include "MatrixBuilder.h"


using namespace std;

string getString(const Direction& direction) {
    switch (direction) {
        case Direction::left:
            return "Izquierda";
        case Direction::right:
            return "Derecha";
        case Direction::up:
            return "Arriba";
        case Direction::down:
            return "Abajo";
        case Direction::back:
            return "Nivel Inferior";
        case Direction::front:
            return "Nivel Superior";
        default:
            return "";
    }
}

GameManager::~GameManager() {
    delete builder;
    delete ranking;
}

bool GameManager::requestUserMove() {
    vector<Direction> moves;

    matrix->addMovesToVector(&moves);

    cout << msgMoves;

    for (size_t i = 0; i < moves.size(); i++) {
        cout << "\t" << i + 1 << ". " << getString(moves[i]) << "\n";
    }
    cout << "\t" << moves.size() + 1 << ". Terminar juego.\n";
    cout << "\t" << moves.size() + 2 << ". Reiniciar juego.\n";

    size_t option = getInteger(msgOption, 1, moves.size() + 2);

    if (moves.size() + 1 == option) {
        return false;
    } else if (moves.size() + 2 == option) {
        cout << "\nPunteo antes del reinicio: " << matrix->calculateScore() << " puntos.";
        cout << "\nReinicio en progreso...";
        builder->resetMatrix();
        matrix = builder->getMatrix();
        matrix->print();
        return true;
    }
    matrix->moveTo(moves[option - 1]);
    matrix->print();

    size_t score = matrix->isWinnerWinnerChickenDinner();
    if (score != 0) {
        cout << "\n\nFelicidades, acaba de ganar.";
        return false;
    }

    return true;
}

bool GameManager::requestGameOption() {
    cout << msgMoves;

    cout << "\t" << 1 << ". Iniciar una partida.\n";
    cout << "\t" << 2 << ". Mostrar registros.\n";
    cout << "\t" << 3 << ". Salir.\n";

    size_t option = getInteger(msgOption, 1, 3);

    switch (option) {
        case 1:
            delete builder;
            builder = new MatrixBuilder();
            matrix = builder->getMatrix();
            initGame();
            break;

        case 2:
            if (ranking != nullptr) {
                cout << "\n No. |    Jugador     | Total de pasos |    Puntaje     |  Tiempo jugado";
                cout << "\n------------------------------------------------------------------";
                ranking->print();
            } else {
                cout << "\nNo existen registros previos. Vuelva despues de jugar una partida\n";
            }
            break;

        default:
            return false;
    }
    return true;
}

void GameManager::manageGame() {
    while (requestGameOption());
}

void GameManager::initGame() {
    auto start = chrono::steady_clock::now();
    string name;
    size_t rank = 1;

    size_t score = matrix->isWinnerWinnerChickenDinner();
    if (score != 0) {
        cout << "\n\nFelicidades, acaba de ganar.";
    } else {
        while (requestUserMove());
    }
    std::chrono::duration<double> finalTime = chrono::steady_clock::now() - start;

    cout << "\nEl punteo obtenido es de: " << matrix->calculateScore() << " puntos.";
    cout << "\nPara guardar y mostrar su hazaña necesitaremos que nos proporcione";
    cout << "\n\tSu nombre:\t";

    cin >> name;

    auto *playerRank = new Player(name, matrix->getSteps(), finalTime.count(), matrix->calculateScore());
    if (ranking == nullptr) {
        ranking = new Ranking(playerRank);
    } else {
        rank = ranking->insert(playerRank);
        ranking = ranking->getRoot();
    }
    cout << "\n\nCalculando su posicion en el ranking del juego, espere un momento... " << endl;
    cout << "Con un total de " << playerRank->steps << " pasos..." << endl;
    cout << "Con " << playerRank->score << " puntos totales..." << endl;
    cout << "Despues de una partida de " << playerRank->gameTime << " segundos..." << endl;
    cout << "Su posicion fue " << rank << "° lugar";
}
