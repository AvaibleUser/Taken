#ifndef TAKEN_NODE_HPP
#define TAKEN_NODE_HPP

struct Node {
private:
    Node *left;
    Node *right;
    Node *up;
    Node *down;
    Node *behind;
    Node *front;

public:
    int data = 0;

    Node(int data, Node *left, Node *right, Node *up, Node *down, Node *behind, Node *front) : data(data), left(left),
                                                                                               right(right), up(up),
                                                                                               down(down),
                                                                                               behind(behind),
                                                                                               front(front) {}

    static Node *getSingleNode(int data);

    [[nodiscard]] Node *getLeft() const;

    void setLeft(Node *node);

    [[nodiscard]] Node *getRight() const;

    void setRight(Node *node);

    [[nodiscard]] Node *getUp() const;

    void setUp(Node *node);

    [[nodiscard]] Node *getDown() const;

    void setDown(Node *node);

    [[nodiscard]] Node *getBehind() const;

    void setBehind(Node *node);

    [[nodiscard]] Node *getFront() const;

    void setFront(Node *node);
};

#endif //TAKEN_NODE_HPP

Node *Node::getSingleNode(int data) {
    return new Node(data, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
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

Node *Node::getBehind() const {
    return behind;
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

void Node::setBehind(Node *node) {
    this->behind = node;
    node->front = this;
}

void Node::setFront(Node *node) {
    this->front = node;
    node->behind = this;
}
