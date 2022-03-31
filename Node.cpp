#include <iostream>
#include "Node.h"

Node::Node(size_t data) : data(data) {}

Node::~Node() {
    delete front;
    if (back == nullptr) {
        delete down;
        if (up == nullptr) {
            delete right;
        }
    }
}

Node *Node::getLeft() const {
    return left;
}

Node *Node::getRight() const {
    return right;
}

Node *Node::getUp() const {
    return up;
}

Node *Node::getDown() const {
    return down;
}

Node *Node::getBack() const {
    return back;
}

Node *Node::getFront() const {
    return front;
}

void Node::setLeft(Node *node) {
    this->left = node;
    node->right = this;
}

void Node::setRight(Node *node) {
    this->right = node;
    node->left = this;
}

void Node::setUp(Node *node) {
    this->up = node;
    node->down = this;
}

void Node::setDown(Node *node) {
    this->down = node;
    node->up = this;
}

void Node::setBack(Node *node) {
    this->back = node;
    node->front = this;
}

void Node::setFront(Node *node) {
    this->front = node;
    node->back = this;
}
