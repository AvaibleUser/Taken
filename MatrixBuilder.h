#ifndef TAKEN_MATRIXBUILDER_H
#define TAKEN_MATRIXBUILDER_H


#include <string>
#include "Matrix.h"


class MatrixBuilder {
private:
    Matrix *matrix = nullptr;
    std::vector<size_t> info;

    const std::string msgRequest = "\n¿Como quiere iniciar el juego? (ingrese el numero de la opcion que desea escoger):\n"
                                   "\t1. Con datos aleatorios.\n"
                                   "\t2. Con datos de un archivo (csv).\n"
                                   "\t3. Con datos ingresados en consola.\n";

    const std::string msgValues = "A continucacion ingrese las dimensiones del juego (ancho, alto, profundidad):\n";

    const std::string msgOption = "\n\t\tOpcion:\t";

    void requestTakenData(size_t width, size_t height, size_t depth);

    void readValuesFromFile(size_t width, size_t height, size_t depth);

    void readValuesFromConsole(size_t width, size_t height, size_t depth);

    void requestTakenDimensions();

public:
    MatrixBuilder();

    ~MatrixBuilder();

    void resetMatrix();

    Matrix *getMatrix();
};


#endif //TAKEN_MATRIXBUILDER_H
