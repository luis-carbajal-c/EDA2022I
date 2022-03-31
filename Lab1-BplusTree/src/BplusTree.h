#include <vector>

struct Leaf {
    Leaf();
};

struct Node {
    std::vector<int> keys;
    std::vector<Node*> children;
    Node* parent;

    Node();
};

class BplusTree {
private:
    Node* root;
    int m;

public:
    BplusTree();
    ~BplusTree();

    void insertar(int value);
    void borrar(int value);
};