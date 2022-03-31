#ifndef TAKEN_NODE_H
#define TAKEN_NODE_H


class Node {

private:
    Node *left = nullptr;
    Node *right = nullptr;
    Node *up = nullptr;
    Node *down = nullptr;
    Node *back = nullptr;
    Node *front = nullptr;

public:
    size_t data = 0;

    explicit Node(size_t data);

    ~Node();

    [[nodiscard]] Node *getLeft() const;

    void setLeft(Node *node);

    [[nodiscard]] Node *getRight() const;

    void setRight(Node *node);

    [[nodiscard]] Node *getUp() const;

    void setUp(Node *node);

    [[nodiscard]] Node *getDown() const;

    void setDown(Node *node);

    [[nodiscard]] Node *getBack() const;

    void setBack(Node *node);

    [[nodiscard]] Node *getFront() const;

    void setFront(Node *node);
};


#endif //TAKEN_NODE_H
