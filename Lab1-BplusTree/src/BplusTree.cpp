#include "BplusTree.h"

#include <queue>
#include <iostream>
#include <math.h>
#include <fstream>

Node::Node() {
    isLeaf = false;
}

BplusTree::BplusTree(){
    root = nullptr;
    m = 21;
}

BplusTree::BplusTree(int m){
    root = nullptr;
    this->m = m;
}

BplusTree::~BplusTree() {
    destroyRecursive(root);
}

void BplusTree::destroyRecursive(Node* node) {
    if (node) {
        for (auto elem : node->children) {
            destroyRecursive(elem);
        }
        delete node;
    }
}

void BplusTree::insertar(int value) {
    if (root == nullptr) {
        root = new Node();
        root->keys.push_back(value);
        root->isLeaf = true;
    } else {
        Node* current = root;
        Node* parent;

        while (!current->isLeaf) {
            parent = current;
            for (int i = 0; i < current->keys.size(); i++) {
                if (value < current->keys[i]) {
                    current = current->children[i];
                    break;
                }
                if (i == current->keys.size() - 1) {
                    current = current->children[i+1];
                    break;
                }
            }
        }

        if (current->keys.size() < m - 1) {
            int cont = 0;
            while (current->keys[cont] < value && cont < current->keys.size()) cont++;
            current->keys.insert(current->keys.begin() + cont, value);
        } else {
            Node* newNode = new Node();
            newNode->isLeaf = true;

            std::vector<int> tempKeys = current->keys;
            int cont = 0;
            while (tempKeys[cont] < value && cont < tempKeys.size()) cont++;
            tempKeys.insert(tempKeys.begin() + cont, value);

            current->keys.clear();
            for (int i = 0; i < floor(m/2); i++) current->keys.push_back(tempKeys[i]);
            for (int i = floor(m/2); i < tempKeys.size(); i++) newNode->keys.push_back(tempKeys[i]);

            if (current == root) {
                Node* newParent = new Node();
                newParent->keys.push_back(newNode->keys[0]);
                newParent->children.push_back(current);
                newParent->children.push_back(newNode);
                root = newParent;
            } else {
                insertarUtil(newNode, parent, newNode->keys[0]);
            }
        }
    }
}

void BplusTree::insertarUtil(Node* node, Node* parent, int value) {
    int cont;
    if (parent->keys.size() < m - 1) {
        cont = 0;
        while (parent->keys[cont] < value && cont < parent->keys.size()) cont++;
        parent->keys.insert(parent->keys.begin() + cont, value);
        parent->children.insert(parent->children.begin() + cont + 1, node);
    } else {
        Node* newNode = new Node();

        std::vector<int> tempKeys = parent->keys;
        std::vector<Node*> tempChildren = parent->children;

        cont = 0;
        while (tempKeys[cont] < value && cont < tempKeys.size()) cont++;
        tempKeys.insert(tempKeys.begin() + cont, value);
        tempChildren.insert(tempChildren.begin() + cont + 1, node);

        parent->keys.clear();
        parent->children.clear();
        for (int i = 0; i < floor(m/2); i++) {
            parent->keys.push_back(tempKeys[i]);
            parent->children.push_back(tempChildren[i]);
        }
        parent->children.push_back(tempChildren[floor(m/2)]);
        for (int i = floor(m/2) + 1; i < tempKeys.size(); i++) {
            newNode->keys.push_back(tempKeys[i]);
            newNode->children.push_back(tempChildren[i]);
        }
        newNode->children.push_back(tempChildren[tempKeys.size()]);

        if (parent == root) {
            Node* newParent = new Node();
            newParent->keys.push_back(tempKeys[floor(m/2)]);
            newParent->children.push_back(parent);
            newParent->children.push_back(newNode);
            root = newParent;
        } else {
            insertarUtil(newNode, getParent(root, parent), tempKeys[floor(m/2)]);
        }
    }
}

void BplusTree::borrar(int value) {
    return;
}

void BplusTree::bfs() {
    std::ofstream outfile("bfs.txt");

    if (root == nullptr) return;

    std::queue<Node*> q;
    q.push(root);

    int cont = 1;
    while (!q.empty()) {
        Node* node = q.front();
        outfile << "Node " << cont++ << ": ";
        for (auto elem : node->keys) {
            outfile << elem << " ";
        }
        outfile << std::endl;
        q.pop();

        for (auto elem : node->children) {
            q.push(elem);
        }
    }

    outfile.close();
}

Node* BplusTree::getParent(Node* current, Node* child) {
    Node* parent;
    if (current->isLeaf || current->children[0]->isLeaf) return nullptr;

    for (int i = 0; i < current->children.size(); i++) {
        if (current->children[i] == child) {
            parent = current;
            return parent;
        } else {
            parent = getParent(current->children[i], child);
            if (parent != nullptr) return parent;
        }
    }

    return parent;
}