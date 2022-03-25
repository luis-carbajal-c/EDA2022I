#ifndef RBTREE_H
#define RBTREE_H

#include <vector>

// Lista de colores del arbol
enum Color {RED,BLACK};

struct Nodo{
    // Atributos
    int dato;
    int color;

    // Relacion con otros Nodos
    Nodo *left;
    Nodo *right;
    Nodo *father;

    // Constructor
    Nodo(int);
};

class RBtree
{
private:
    Nodo *root;
    Nodo *insertarNodo(Nodo* &, Nodo* &);
    void corregirArbol(Nodo* &);

    int getColor(Nodo* &);
    void setColor(Nodo* &, int );

    void rotarIzquierda(Nodo* &);
    void rotarDerecha  (Nodo* &);

    // Funciones de utilidad para realizar recurrencia en los recorridos
    void inorderUtil(Nodo* root, std::vector<int>* v);
    void preorderUtil(Nodo* root, std::vector<int>* v);
    void postorderUtil(Nodo* root, std::vector<int>* v);

public:
    RBtree();
    void insertar(int);

    // Recorridos
    std::vector<int> inorder();
    std::vector<int> preorder();
    std::vector<int> postorder();

    // Eliminacion
    void eliminarNodo(int);

    ~RBtree();
};






#endif