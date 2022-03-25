#include <iostream>
#include "rbtree.h"
#include "rbtree.cpp"

int main() {
    RBtree rbt;
    rbt.insertar(5);
    rbt.insertar(1);
    rbt.insertar(10);
    rbt.insertar(4);
    rbt.insertar(3);
    rbt.insertar(8);

    std::cout << "valores insertados: 5 1 10 4 3 8\n";
    
    std::vector<int> v1 = rbt.inorder();
    std::cout << "\ninorder: ";
    for (auto elem : v1) {
        std::cout << elem << " ";
    }

    std::vector<int> v2 = rbt.preorder();
    std::cout << "\npreorder: ";
    for (auto elem : v2) {
        std::cout << elem << " ";
    }

    std::vector<int> v3 = rbt.postorder();
    std::cout << "\npostorder: ";
    for (auto elem : v3) {
        std::cout << elem << " ";
    }

    std::cout << "\n\nnodos eliminados: - -\n";

    return 0;
}