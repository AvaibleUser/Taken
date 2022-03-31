#ifndef TAKEN_MATRIX_H
#define TAKEN_MATRIX_H


#include <vector>
#include "Node.h"
#include "Direction.h"


using std::vector;

class Matrix {

private:
    Node *root = nullptr;
    Node *anchor = nullptr;
    size_t width = 0;
    size_t height = 0;
    size_t depth = 0;
    size_t steps = 0;

    static void fillArrayWithRandomValues(size_t *arr, size_t size);

    static void shuffle(size_t *arr, size_t size);

    void createMatrix(size_t w, size_t h, size_t d, size_t *arr);

public:
    Matrix(size_t width, size_t height, size_t depth);
    Matrix(size_t width, size_t height, size_t depth, size_t *arr);
    ~Matrix();

    void print();

    void moveTo(Direction direction);

    void addMovesToVector(vector<Direction> *directions);

    size_t calculateScore();

    size_t isWinnerWinnerChickenDinner();

    size_t getWidth() const;

    size_t getHeight() const;

    size_t getDepth() const;

    size_t getSteps() const;
};


#endif //TAKEN_MATRIX_H
