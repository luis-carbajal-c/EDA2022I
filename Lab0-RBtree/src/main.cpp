#include <iostream>
#include "rbtree.h"
#include "rbtree.cpp"

int main() {
    // Crear RBtree y llenar de datos iniciales
    RBtree rbt;
    rbt.insertar(7);
    rbt.insertar(5);
    rbt.insertar(9);
    rbt.insertar(4);
    rbt.insertar(3);
    rbt.insertar(6);
    rbt.insertar(10);
    rbt.insertar(8);
    rbt.insertar(12);

    std::cout << "valores insertados: 7, 5, 9, 4, 3, 6, 10, 8 y 12\n";
    
    // Hacer los tres recorridos sobre el RBtree creado
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
    
    // Eliminar algunos nodos del RBtree
    rbt.eliminarNodo(4);
    rbt.eliminarNodo(9);
    rbt.eliminarNodo(10);
    std::cout << "\n\nnodos eliminados: 4, 9 y 10\n";

    // Volver a hacer los recorridos
    v1 = rbt.inorder();
    std::cout << "\ninorder: ";
    for (auto elem : v1) {
        std::cout << elem << " ";
    }

    v2 = rbt.preorder();
    std::cout << "\npreorder: ";
    for (auto elem : v2) {
        std::cout << elem << " ";
    }

    v3 = rbt.postorder();
    std::cout << "\npostorder: ";
    for (auto elem : v3) {
        std::cout << elem << " ";
    }

    return 0;
}