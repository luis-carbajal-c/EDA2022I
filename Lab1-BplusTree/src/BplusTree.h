#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <vector>

struct Node {
    std::vector<int> keys;
    std::vector<Node*> children;
    bool isLeaf;

    Node();
};

class BplusTree {
private:
    Node* root;
    int m;

    void insertarUtil(Node* node, Node* parent, int value);
    void destroyRecursive(Node* node);
    Node* getParent(Node* current, Node* child);

public:
    BplusTree();
    BplusTree(int m);
    ~BplusTree();

    void insertar(int value);
    void borrar(int value);
    void bfs();
};



#endif