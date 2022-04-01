#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <vector>

struct Node {
    std::vector<int> keys;
    std::vector<Node*> children;
    Node* parent;
    bool isLeaf;

    Node();
};

class BplusTree {
private:
    Node* root;
    int m;

    void insertarUtil(Node* node, Node* parent, int value);

public:
    BplusTree();
    BplusTree(int m);
    ~BplusTree();

    void insertar(int value);
    void borrar(int value);
    void bfs();
};



#endif