#include <iostream>
#include "BplusTree.h"
#include <fstream>
#include <chrono>

// g++ -o main .\BplusTree.cpp .\BplusTree.h .\main.cpp

int main() {
    // Read file
    std::ifstream texto;
    texto.open("../output.txt");

    int* datos = new int[1000000];
    int element;
    if (texto.is_open()) {
        int i = 0;
        while (texto >> element) {
            datos[i++] = element;
        }
    } 
    
    int64_t tiempoInseccion = 0;
    for (int t=0; t<10; ++t){
        
        auto tree = new BplusTree();
        
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        for (int i=0; i<1000000; ++i){
            tree->insertar( datos[i] );
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        // Calcular tiempo
        auto tiempo = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        tiempoInseccion += tiempo;
    }

    std::cout << tiempoInseccion << std::endl;

    delete[] datos;
    return 0;

    /* Test using visualization tool:
    
    auto bpt = new BplusTree(4);

    bpt->insertar(1);
    bpt->insertar(4);
    bpt->insertar(7);
    bpt->insertar(10);
    bpt->insertar(17);
    bpt->insertar(21);
    bpt->insertar(31);
    bpt->insertar(25);
    bpt->insertar(19);
    bpt->insertar(20);
    bpt->insertar(28);
    bpt->insertar(42);

    bpt->insertar(27);
    bpt->insertar(26);
    bpt->insertar(29);
    bpt->insertar(30);

    bpt->insertar(45);
    bpt->insertar(43);
    bpt->insertar(50);
    bpt->insertar(52);
    bpt->insertar(51);
    bpt->insertar(53);
    bpt->insertar(56);
    bpt->insertar(55);
    bpt->insertar(54);
    bpt->insertar(57);
    bpt->insertar(58);
    bpt->insertar(59);
    bpt->insertar(60);

    bpt->bfs();*/
}