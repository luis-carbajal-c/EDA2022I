#include <algorithm> 
#include "rbtree.h"

Nodo::Nodo(int dato){
    this->dato = dato;
    color = RED;
    
    left   = nullptr;
    right  = nullptr;
    father = nullptr;
}


int RBtree::getColor(Nodo* &puntero){
    if (puntero == nullptr) return BLACK;
    return puntero->color;
}

void RBtree::setColor(Nodo* &puntero, int color){
    if (puntero == nullptr) return;
    puntero->color = color;
}

/*          
 *        X                            Y
 *       / \     Rotar izquierda      / \
 *      A   Y    --------------->    X   C
 *         / \                      / \
 *        B   C                    A   B
 * 
 * La función se aplica a X
 */
void RBtree::rotarIzquierda(Nodo* &puntero){
    // Nodo Y
    Nodo *hijoDerecho = puntero->right;
    
    
    puntero->right = hijoDerecho->left;         // Asignar como hijo derecho de X a B
    if (puntero->right != nullptr)
        puntero->right->father = puntero;       // Asignar como nuevo padre de B a X


    hijoDerecho->father = puntero->father;      // Asignar que el nuevo padre de Y sea el padre de X
                                                // Esto es para conectar con el resto del arbol
    // Asignar la Y como hijo derecho o izquierdo 
    // En el paso anterior contectamos a Y con el resto del arbol, ahora Y será asignado como hijo del nodo superior
    if (puntero->father == nullptr)
        root = hijoDerecho;                     // Si no hay padre, significa que llegamos a la raiz
    else if (puntero == puntero->father->left)  
        puntero->father->left = hijoDerecho;    // Antes de la rotacion, X era el hijo izquiero
    else
        puntero->father->right = hijoDerecho;   // Antes de la rotacion, X era el hijo derecho

    hijoDerecho->left = puntero;                // Asignar a X como hijo izquierdo de Y
    puntero->father = hijoDerecho;              // Asignar a Y como padre de X
}

/*         
 *        Y                        X
 *       / \     Rotar derecha    / \
 *      X   C    ------------->  A   Y
 *     / \                          / \
 *    A   B                        B   C
 * 
 * La función se aplica a Y
 */
void RBtree::rotarDerecha(Nodo* &puntero){
    // Nodo X
    Nodo *hijoIzquierdo = puntero->left;        


    puntero->left = hijoIzquierdo->right;       // Asignar como hijo izquierdo de Y a B
    if (puntero->left != nullptr)
        puntero->left->father = puntero;        // Asignar como nuevo padre de B a Y


    hijoIzquierdo->father = puntero->father;    // Asignar que el nuevo padre de X sea el padre Y
                                                // Esto es para conectar con el resto del arbol
    // Asignar la X como hijo derecho o izquierdo 
    // En el paso anterior contectamos a X con el resto del arbol, ahora X será asignado como hijo del nodo superior
    if (puntero->father == nullptr)
        root = hijoIzquierdo;                   // Si no hay padre, significa que llegamos a la raiz
    else if (puntero == puntero->father->left)
        puntero->father->left = hijoIzquierdo;  // Antes de la rotacion, Y era el hijo izquiero
    else
        puntero->father->right = hijoIzquierdo;  // Antes de la rotacion, Y era el hijo derecho


    hijoIzquierdo->right = puntero;              // Asignar a Y como hijo derecho de X
    puntero->father = hijoIzquierdo;             // Asignar a X como padre de Y
}



Nodo* RBtree::insertarNodo(Nodo* &padre, Nodo* &puntero){
    // Arbol vacio
    if (padre == nullptr) return puntero;
    
    // Si el nuevo numero es menor al padre
    if(puntero->dato < padre->dato){
        padre->left = insertarNodo(padre->left,puntero);
        padre->left->father = padre;
    }
    // Si el nuevo numero es mayo al padre
    else if (puntero->dato > padre->dato){
        padre->right = insertarNodo(padre->right,puntero);
        padre->right->father = padre;
    }
    return padre;
}


void RBtree::corregirArbol(Nodo* &puntero){
    Nodo* padre  = nullptr;
    Nodo* abuelo = nullptr;
    while ( puntero != root &&  getColor(puntero)==RED && getColor(puntero->father)==RED ){
        padre  = puntero->father;
        abuelo = padre  ->father;

        // El padre esta a la izquierda
        if (padre == abuelo->left){
            Nodo* tio = abuelo->right;

            // CASO I: padre y tio son rojos
            if(  getColor(tio) ==RED ){
                setColor(padre ,BLACK);
                setColor(tio   ,BLACK);
                setColor(abuelo,RED  );
                puntero = abuelo;
            }
            else{
                // CASO II: padre y el hijo tienen distintas direcciones
                if(puntero == padre->right){
                    rotarIzquierda(padre);
                    puntero = padre;
                    padre = puntero->father;
                }

                // CASO III: padre y el hijo tienen la misma dirección
                rotarDerecha(abuelo);
                std::swap(padre->color,abuelo->color);
                puntero = padre;
            }
        }

        // El padre esta a la derecha
        else{
            Nodo* tio = abuelo->left;

            // CASO I: padre y tio son rojos
            if(  getColor(tio) ==RED ){
                setColor(padre ,BLACK);
                setColor(tio   ,BLACK);
                setColor(abuelo,RED  );
                puntero = abuelo;
            }
            else{
                // CASO II: padre y el hijo tienen distintas direcciones
                if(puntero == padre->left){
                    rotarDerecha(padre);
                    puntero = padre;
                    padre = puntero->father;
                }

                // CASO III: padre y el hijo tienen la misma dirección
                rotarIzquierda(abuelo);
                std::swap(padre->color,abuelo->color);
                puntero = padre;
            }
        }
    }
    
    setColor(root, BLACK);
}

void RBtree::insertar(int dato){
    Nodo *puntero = new Nodo(dato);
    root = insertarNodo(root,puntero);
    corregirArbol(puntero);
}

RBtree::RBtree(){
    root = nullptr;
}

RBtree::~RBtree(){
}

// *****************************
// ******* LAB0 - RBtree *******
// *****************************

// Recorridos

std::vector<int> RBtree::inorder(){
    std::vector<int> v; // Vector con nodos en orden inorder
    inorderUtil(root, &v); // Llamada recursiva
    return v;
}

void RBtree::inorderUtil(Nodo* root, std::vector<int>* v) {
    // Condicion de parada (root == nullptr)
    if (root != nullptr) {
        inorderUtil(root->left, v);     // Left
        v->push_back(root->dato);       // Root
        inorderUtil(root->right, v);    // Right
    }
}

std::vector<int> RBtree::preorder(){
    std::vector<int> v; // Vector con nodos en orden preorder
    preorderUtil(root, &v); // Llamada recursiva
    return v;
}

void RBtree::preorderUtil(Nodo* root, std::vector<int>* v) {
    // Condicion de parada (root == nullptr)
    if (root != nullptr) {
        v->push_back(root->dato);       // Root
        preorderUtil(root->left, v);    // Left
        preorderUtil(root->right, v);   // Right
    }
}

std::vector<int> RBtree::postorder(){
    std::vector<int> v; // Vector con nodos en orden preorder
    postorderUtil(root, &v); // Llamada recursiva
    return v;
}

void RBtree::postorderUtil(Nodo* root, std::vector<int>* v) {
    // Condicion de parada (root == nullptr)
    if (root != nullptr) {
        postorderUtil(root->left, v);   // Left
        postorderUtil(root->right, v);  // Right
        v->push_back(root->dato);       // Root
    }
}

// Eliminacion

void RBtree::eliminarNodo(int dato) {
    // Si no hay root, retornar
    if (root == nullptr) return;
 
    // Binary search para encontrar el nodo a eliminar
    Nodo *temp = root;
    while (temp != nullptr) {
        if (dato < temp->dato) {
            if (temp->left == nullptr) break;
            else temp = temp->left;
        } else if (dato > temp->dato) {
            if (temp->right == nullptr) break;
            else temp = temp->right;
        } else break;
    }

    // Llamar a la funcion de utilidad que permite eliminar el nodo
    eliminarNodoUtil(temp);
}

void RBtree::eliminarNodoUtil(Nodo* nodo) {
    // Para todos los casos se requiere un nodo que actue como "hijo" para reemplazar al eliminado
    Nodo* hijo;

    // Si el nodo tiene dos hijos, el "hijo" va a ser el nodo menor del subarbol derecho
    if (nodo->left != nullptr && nodo->right != nullptr) {
        Nodo* temp = nodo->right;
        while(temp->left != nullptr) temp = temp->left;
        hijo = temp;
    }
    // Si el nodo no tiene hijos, el "hijo" va a ser un nodo vacio
    else if (nodo->left == nullptr && nodo->right == nullptr) hijo = nullptr;
    // Si el nodo tiene un solo hijo, ese va a ser el "hijo"
    if (nodo->left != nullptr) hijo = nodo->left;
    else hijo = nodo->right;

    // Se manejan primero los casos en los que el nodo a eliminar no tiene hijos
    if (hijo == nullptr) {
        // Si el nodo a eliminar es la raiz, solo se elimina
        if (nodo == root) {
            root = nullptr;
            delete nodo;
        } else {
            // Si el nodo a eliminar y el "hijo" son negros (este ultimo siempre lo es porque es nullptr)
            // hay un double black y se llama a la funcion corregirEliminacion para arreglar el caso
            if (getColor(nodo) == BLACK) {
                corregirEliminacion(nodo);
            }

            // Se elimina el nodo del arbol actualizando su padre para que apunte a nulo
            if (nodo == nodo->father->left) nodo->father->left = nullptr;
            else nodo->father->right = nullptr;
        }
        // Se libera memoria
        delete nodo;
        return;
    }

    // Si no se entro en la condicion anterior, entonces se verifica si el nodo tiene solo un hijo
    if (nodo->left == nullptr || nodo->right == nullptr) {
        // Si el nodo a eliminar es la raiz, como solo tiene un hijo basta con darle al padre el valor
        // del hijo y eliminarlo
        if (nodo == root) {
            nodo->dato = hijo->dato;
            nodo->left = nullptr;
            nodo->right = nullptr;
            delete hijo;
        } else {
            // Si el nodo no es la raiz, se elimina del arbol reemplazandolo por el hijo
            if (nodo == nodo->father->left) nodo->father->left = hijo;
            else nodo->father->right = hijo;
            hijo->father = nodo->father;

            // Si el nodo a eliminar o el hijo son rojos, se pinta el hijo de negro
            if (getColor(nodo) == RED || getColor(hijo) == RED) setColor(hijo, BLACK);
            // Si el nodo a eliminar y el "hijo" son negros hay un double black y se llama a la 
            // funcion corregirEliminacion para arreglar el caso
            else corregirEliminacion(hijo);

            // Se libera memoria
            delete nodo;
        }
        return;
    }

    // En el ultimo caso en el que la funcion no retorna aun es que tenga 2 hijos
    // Para esto se intercambian los valores del nodo a eliminar y el "hijo" y se llama recursivamente
    int temp;
    temp = nodo->dato;
    nodo->dato = hijo->dato;
    hijo->dato = temp;

    eliminarNodoUtil(hijo);
}

void RBtree::corregirEliminacion(Nodo* nodo) {
    // Caso base
    if (nodo == root) return;

    Nodo* padre = nodo->father;
    // Hallar hermano del nodo
    Nodo* hermano;
    if (nodo == padre->left) hermano = padre->right;
    else hermano = padre->left;

    // Si no hay hermano, el double black se mueve hacia arriba 
    if (hermano == nullptr) corregirEliminacion(padre);
    else {
        // Si el hermano es rojo, se cambia a negro, el padre se cambia a rojo, se rota sobre el padre
        // en la misma direccion que la posicion del nodo y se vuelve a llamar sobre el nodo
        if (getColor(hermano) == RED) {
            setColor(padre, RED);
            setColor(hermano, BLACK);

            if (nodo == padre->left) rotarIzquierda(padre);
            else rotarDerecha(padre);

            corregirEliminacion(nodo);
        } else {
            // Si el hermano tiene un hijo rojo se van a realizar rotaciones dependiendo de cual de
            // los hijos es rojo y si el hermano es hijo izquierdo o derecho del padre
            if (getColor(hermano->left) == RED || getColor(hermano->right) == RED) {
                if (getColor(hermano->left) == RED) {
                    if (hermano == padre->left) {
                        setColor(hermano->left, getColor(hermano));
                        setColor(hermano, getColor(padre));
                        rotarDerecha(padre);
                    } else {
                        setColor(hermano->left, getColor(padre));
                        rotarDerecha(hermano);
                        rotarIzquierda(padre);
                    }
                } else {
                    if (hermano == padre->left) {
                        setColor(hermano->right, getColor(padre));
                        rotarIzquierda(hermano);
                        rotarDerecha(padre);
                    } else {
                        setColor(hermano->right, getColor(hermano));
                        setColor(hermano, getColor(padre));
                        rotarIzquierda(padre);
                    }
                }
                // Se cambia el color del padre a negro
                setColor(padre, BLACK);
            } 
            // Si el hermano no tiene hijos rojos, se cambia de color a rojo y, si el padre es negro,
            // se vuelve a llamar a la funcion sobre el padre, de lo contrario se cambia a negro
            else {
                setColor(hermano, RED);
                if (getColor(padre) == BLACK) corregirEliminacion(padre);
                else setColor(padre, BLACK);
            }
        }
    }
}

