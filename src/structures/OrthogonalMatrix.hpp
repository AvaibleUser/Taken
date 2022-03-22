#ifndef TAKEN_ORTHOGONALMATRIX_HPP
#define TAKEN_ORTHOGONALMATRIX_HPP

#include <iostream>
#include <random>
#include <algorithm>
#include "Node.hpp"

struct OrthogonalMatrix {
private:
    Node *root;
    int width;
    int height;
    int depth;

    static void fillArrayWithRandomValues(int *arr, int size);

    static void shuffle(int *arr, int size);
public:
    OrthogonalMatrix(int width, int height, int depth);

    void print();
};

#endif //TAKEN_ORTHOGONALMATRIX_HPP

OrthogonalMatrix::OrthogonalMatrix(int w, int h, int d) {
    int size = w * h * d;
    width = w;
    height = h;
    depth = d;

    int arr[size];
    fillArrayWithRandomValues(arr, size);

    root = Node::getSingleNode(arr[0]);
    Node *widthAnchor = root;
    for (int m = 0, i = 1; m < width; m++, i++) {
        Node *heightAnchor = widthAnchor;
        for (int n = 0; n < height; n++, i++) {
            Node *depthAnchor = heightAnchor;
            for (int o = 0; o < depth - 1; o++, i++) {
                depthAnchor->setFront(Node::getSingleNode(arr[i]));

                if (depthAnchor->getUp() != nullptr) {
                    depthAnchor->getFront()->setUp(depthAnchor->getUp()->getFront());
                }
                if (depthAnchor->getLeft() != nullptr) {
                    depthAnchor->getFront()->setLeft(depthAnchor->getLeft()->getFront());
                }

                depthAnchor = depthAnchor->getFront();
            }
            if (n == height - 1) break;
            heightAnchor->setDown(Node::getSingleNode(arr[i]));

            if (heightAnchor->getLeft() != nullptr) {
                heightAnchor->getDown()->setLeft(heightAnchor->getLeft()->getDown());
            }
            heightAnchor = heightAnchor->getDown();
        }
        if (m == width - 1) break;
        widthAnchor->setRight(Node::getSingleNode(arr[i]));
        widthAnchor = widthAnchor->getRight();
    }
}

void OrthogonalMatrix::print() {
    Node *depthAnchor = root;
    for (int o = 0; o < depth; o++) {
        Node *widthAnchor = depthAnchor;

        std::cout << std::endl << std::endl << "Nivel ";
        std::cout << o + 1 << std::endl << "-------------------";
        for (int n = 0; n < height; n++) {
            Node *heightAnchor = widthAnchor;

            std::cout << std::endl << "| ";
            for (int m = 0; m < width; m++) {
                std::string str;
                int data = heightAnchor->data;
                if (heightAnchor->data == 0)
                    str = "  x";
                else if (heightAnchor->data < 10)
                    str = "  " + std::to_string(data);
                else if (heightAnchor->data < 100)
                    str = " " + std::to_string(data);
                else
                    str = std::to_string(data);
                std::cout << str << " | ";
                heightAnchor = heightAnchor->getRight();
            }
            widthAnchor = widthAnchor->getDown();
        }
        depthAnchor = depthAnchor->getFront();
    }
}

void OrthogonalMatrix::fillArrayWithRandomValues(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    shuffle(arr, size);
}

void OrthogonalMatrix::shuffle(int *arr, int size) {
    unsigned seed = time(nullptr);
    std::shuffle(arr, arr + size, std::default_random_engine(seed));
}
