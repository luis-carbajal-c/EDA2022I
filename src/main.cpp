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
    
    std::vector<int> v1 = rbt.inorder();
    std::cout << "inorder: ";
    for (auto i : v1) {
        std::cout << i << " ";
    }

    std::vector<int> v2 = rbt.preorder();
    std::cout << "\npreorder: ";
    for (auto i : v2) {
        std::cout << i << " ";
    }

    std::vector<int> v3 = rbt.postorder();
    std::cout << "\npostorder: ";
    for (auto i : v3) {
        std::cout << i << " ";
    }

    return 0;
}