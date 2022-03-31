#include <iostream>
#include <limits>
#include "MatrixBuilder.h"
#include "UtilityFunctions.h"
#include "Reader.h"


using namespace std;

MatrixBuilder::MatrixBuilder() {
    while (matrix == nullptr)
        requestTakenDimensions();
    matrix->print();
}

MatrixBuilder::~MatrixBuilder() {
    delete matrix;
}

void MatrixBuilder::requestTakenDimensions() {
    cout << msgValues;
    size_t width = getInteger("\tAncho:\t", 1, 1000);

    size_t height = getInteger("\tAlto:\t", 1, 1000);

    size_t depth = getInteger("\tNiveles:\t", 1, 1000);

    size_t total = width * height * depth;
    if (total == width || total == height || total == depth) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nLa matriz no puede tener dos dimensiones (o mas) iguales a 1, vuelva a ingresar los datos.\n";
    } else {
        requestTakenData(width, height, depth);

        if (matrix == nullptr) {
            cout << "\nIngrese datos acorde a las dimensiones.\n";
        }
    }
}

void MatrixBuilder::readValuesFromFile(size_t width, size_t height, size_t depth) {
    string path;

    cout << "\n\tDireccion al archivo: ";
    cin >> path;

    Reader readPath(path, true);

    if (readPath.getVectorSize() != width * height * depth) {
        return;
    }
    readPath.copyDataToVector(&info);
    matrix = new Matrix(width, height, depth, readPath.getVectorData());
}

void MatrixBuilder::readValuesFromConsole(size_t width, size_t height, size_t depth) {
    string csv;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n\tValores (en formato csv): ";
    getline(cin, csv, '\n');

    Reader readValues(csv, false);

    size_t size = width * height * depth;
    if (readValues.getVectorSize() != size) {
        return;
    } else {
        const size_t *values = readValues.getVectorData();
        for (int i = 0; i < readValues.getVectorSize(); i++) {
            if (values[i] >= size) {
                return;
            }
        }
    }
    readValues.copyDataToVector(&info);
    matrix = new Matrix(width, height, depth, info.data());

}

void MatrixBuilder::requestTakenData(size_t width, size_t height, size_t depth) {
    string consumeStr;
    cout << msgRequest;

    size_t option = getInteger(msgOption, 1, 3);

    switch (option) {
        case 1:
            matrix = new Matrix(width, height, depth);
            break;

        case 2:
            readValuesFromFile(width, height, depth);
            break;

        default:
            readValuesFromConsole(width, height, depth);
            break;
    }
}

Matrix *MatrixBuilder::getMatrix() {
    return matrix;
}

void MatrixBuilder::resetMatrix() {
    if (matrix != nullptr) {
        size_t width = matrix->getWidth();
        size_t height = matrix->getHeight();
        size_t depth = matrix->getDepth();

        delete matrix;

        if (info.data() == nullptr)
            matrix = new Matrix(width, height, depth);
        else
            matrix = new Matrix(width, height, depth, info.data());
    } else {
        cout << "\n\tNo se encontraron los datos de la matriz";
    }
}
