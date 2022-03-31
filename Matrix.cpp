#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include "Direction.h"
#include "Matrix.h"
#include "Node.h"


using namespace std;

void Matrix::createMatrix(size_t w, size_t h, size_t d, size_t *arr) {
    width = w;
    height = h;
    depth = d;

    root = new Node(arr[0]);
    if (arr[0] == 0) {
        anchor = root;
    }
    Node *depthAnchor = root;
    for (size_t m = 0, i = 1; m < depth; m++, i++) {
        Node *heightAnchor = depthAnchor;
        for (size_t n = 0; n < height; n++, i++) {
            Node *widthAnchor = heightAnchor;
            for (size_t o = 0; o < width - 1; o++, i++) {
                widthAnchor->setRight(new Node(arr[i]));

                if (arr[i] == 0) {
                    anchor = widthAnchor->getRight();
                }
                if (widthAnchor->getUp() != nullptr) {
                    widthAnchor->getRight()->setUp(widthAnchor->getUp()->getRight());
                }
                if (widthAnchor->getBack() != nullptr) {
                    widthAnchor->getRight()->setBack(widthAnchor->getBack()->getRight());
                }

                widthAnchor = widthAnchor->getRight();
            }
            if (n == height - 1) break;
            heightAnchor->setDown(new Node(arr[i]));

            if (arr[i] == 0) {
                anchor = heightAnchor->getDown();
            }
            if (heightAnchor->getBack() != nullptr) {
                heightAnchor->getDown()->setBack(heightAnchor->getBack()->getDown());
            }

            heightAnchor = heightAnchor->getDown();
        }
        if (m == depth - 1) break;
        depthAnchor->setFront(new Node(arr[i]));

        if (arr[i] == 0) {
            anchor = depthAnchor->getFront();
        }

        depthAnchor = depthAnchor->getFront();
    }
}

Matrix::Matrix(size_t width, size_t height, size_t depth) {
    size_t size = width * height * depth;
    size_t arr[size];

    fillArrayWithRandomValues(arr, size);
    createMatrix(width, height, depth, arr);
}

Matrix::Matrix(size_t width, size_t height, size_t depth, size_t *arr) {
    createMatrix(width, height, depth, arr);
}

Matrix::~Matrix() {
    delete root;
}

void Matrix::fillArrayWithRandomValues(size_t *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = i;
    }
    shuffle(arr, size);
}

void Matrix::shuffle(size_t *arr, size_t size) {
    unsigned seed = time(nullptr);
    std::shuffle(arr, arr + size, default_random_engine(seed));
}

void Matrix::print() {
    Node *depthAnchor = root;
    for (size_t o = 0; o < depth; o++) {
        Node *heightAnchor = depthAnchor;

        cout << endl << endl << "Nivel ";
        cout << o + 1 << endl << "-------------------";
        for (size_t n = 0; n < height; n++) {
            Node *widthAnchor = heightAnchor;

            cout << endl << "| ";
            for (size_t m = 0; m < width; m++) {
                string str;
                size_t data = widthAnchor->data;
                if (widthAnchor->data == 0)
                    str = "  x";
                else if (widthAnchor->data < 10)
                    str = "  " + to_string(data);
                else if (widthAnchor->data < 100)
                    str = " " + to_string(data);
                else
                    str = to_string(data);
                cout << str << " | ";
                widthAnchor = widthAnchor->getRight();
            }
            heightAnchor = heightAnchor->getDown();
        }
        depthAnchor = depthAnchor->getFront();
    }
}

void Matrix::moveTo(Direction direction) {
    Node *node;

    switch (direction) {
        case Direction::left:
            node = anchor->getLeft();
            break;
        case Direction::right:
            node = anchor->getRight();
            break;
        case Direction::up:
            node = anchor->getUp();
            break;
        case Direction::down:
            node = anchor->getDown();
            break;
        case Direction::back:
            node = anchor->getBack();
            break;
        case Direction::front:
            node = anchor->getFront();
            break;
    }

    if (node == nullptr) {
        throw invalid_argument("Se intento mover a una direccion inexistente.");
    }
    anchor->data = node->data;
    node->data = 0;
    anchor = node;
    steps++;
}

void Matrix::addMovesToVector(vector<Direction> *directions) {
    if (anchor == nullptr) {
        cout << "No hay ningun espacio vacio en el tablero.";
        return;
    }
    if (anchor->getLeft() != nullptr) {
        directions->push_back(Direction::left);
    }
    if (anchor->getRight() != nullptr) {
        directions->push_back(Direction::right);
    }
    if (anchor->getUp() != nullptr) {
        directions->push_back(Direction::up);
    }
    if (anchor->getDown() != nullptr) {
        directions->push_back(Direction::down);
    }
    if (anchor->getBack() != nullptr) {
        directions->push_back(Direction::back);
    }
    if (anchor->getFront() != nullptr) {
        directions->push_back(Direction::front);
    }
}

size_t Matrix::calculateScore() {
    size_t score = 0;

    Node *depthAnchor = root;
    for (size_t o = 0, i = 1; o < depth; o++) {
        Node *heightAnchor = depthAnchor;
        for (size_t n = 0; n < height; n++) {
            Node *widthAnchor = heightAnchor;
            for (size_t m = 0; m < width; m++, i++) {
                size_t value = widthAnchor->data;
                if (value == i || value == 0 && i == depth * height * width) {
                    score += 2;
                }

                widthAnchor = widthAnchor->getRight();
            }
            heightAnchor = heightAnchor->getDown();
        }
        depthAnchor = depthAnchor->getFront();
    }
    return score;
}

size_t Matrix::isWinnerWinnerChickenDinner() {
    if (anchor->getRight() == nullptr) {
        if (anchor->getDown() == nullptr) {
            if (anchor->getFront() == nullptr) {
                size_t score = calculateScore();
                if (score == 2 * width * height * depth) {
                    return score;
                }
            }
        }
    }
    return 0;
}

size_t Matrix::getWidth() const {
    return width;
}

size_t Matrix::getHeight() const {
    return height;
}

size_t Matrix::getDepth() const {
    return depth;
}

size_t Matrix::getSteps() const {
    return steps;
}
