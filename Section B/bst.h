#include <iostream>
#include "linkedlist.h"
using namespace std;

#ifndef __BINARYSEARCHTREE__CPP__
#define __BINARYSEARCHTREE__CPP__

template <typename K, typename T>
class Node {
    private:
        K key;
        T elem; 
        Node* parent, * left, * right;
    public:
        Node() = default;
        Node(K m_key, T m_elem, Node* m_parent) {
            key = m_key;
            elem = m_elem;
            parent = m_parent;
            left = nullptr;
            right = nullptr;
        }
        Node* getParent() { return parent; }
        Node* getLeft() { return left; }
        Node* getRight() { return right; }
        void setParent(Node* m_parent) { parent = m_parent; }
        void setLeft(Node* node) { left = node; }
        void setRight(Node* node) { right = node; }
        T getElem() { return elem; }
        void setElem(T m_elem) { elem = m_elem; }
        bool hasLeft() { return left != nullptr; }
        bool hasRight() { return right != nullptr; }
        void setKey(K m_key) { key = m_key; }
        K getKey() { return key; }
};
template <typename K, typename T>
class BinaryTree {
    private:
        Node<K, T>* root;
        int s;
    public:
        BinaryTree(): root(), s {0} {}
        Node<K, T>* getRoot() { return root; }
        int size() { return s; }
        bool isEmpty() { return !s; }
        bool isInternal(Node<K, T>* node) { 
            return node->hasLeft() || node->hasRight();
        }
        bool isExternal(Node<K, T>* node) {
            return !node->getLeft() && !node->getRight();
        }
        bool isRoot(Node<K, T>* node) { return node->getParent() == nullptr; }
        void preOder(Node<K, T>* node, void (*visit)(Node<K, T>* m_node)) {
            if (node) {
                visit(node);
                preOder(node->getLeft(), visit);
                preOder(node->getRight(), visit);
            }
        }
        void inOder(Node<K, T>* node, void (*visit)(Node<K, T>* m_node)) {
            if (node) {
                inOder(node->getLeft(), visit);
                visit(node);
                inOder(node->getRight(), visit);
            }
        }
        void postOder(Node<K, T>* node, void (*visit)(Node<K, T>* m_node)) {
            if (node) {
                postOder(node->getLeft(), visit);
                postOder(node->getRight(), visit);
                visit(node);
            }
        }
        Node<K, T>* search(K m_key, Node<K, T>* node, bool op = 0) {
            if (m_key < node->getKey()) {
                if (node->getLeft()) 
                    return search(m_key, node->getLeft(), op);
                if (op) 
                    return node;
                else return nullptr;
            }
            else if (m_key > node->getKey()) {
                if (node->getRight())
                    return search(m_key, node->getRight(), op);
                if (op) 
                    return node;
                else return nullptr;
            } else return node;
        }
        void addNode(K m_key, T x) {
            if (s == 0) {
                Node<K, T>* tmp = new Node<K, T>(m_key, x, nullptr);
                root = tmp;
                s++;
                return;
            }
            Node<K, T>* m_parent = search(m_key, root, 1);
            Node<K, T>* tmp = new Node<K, T>(m_key, x, m_parent);
            if (m_key < m_parent->getKey())
                m_parent->setLeft(tmp);
            else if (m_key > m_parent->getKey())
                m_parent->setRight(tmp);
            else return;
            s++;
        }
        void remove(Node<K, T>* node) {
            Node<K, T>* parentNode {node->getParent()};
            if (!node->hasLeft() && !node->hasRight()) {
                if (parentNode->getLeft() == node)
                    parentNode->setLeft(nullptr);
                else parentNode->setRight(nullptr);
            }
            else if (node->hasLeft()) {
                node->getLeft()->setParent(parentNode);
                if (parentNode->getLeft() == node) 
                    parentNode->setLeft(node->getLeft());
                else parentNode->setRight(node->getLeft());
            }
            else if (node->hasRight()) {
                node->getRight()->setParent(parentNode);
                if (parentNode->getLeft() == node) 
                    parentNode->setLeft(node->getRight());
                else parentNode->setRight(node->getRight());
            }
            delete node;
        }
        Node<K, T>* getLeftest(Node<K, T>* node) {
            Node<K, T>* m_node {node};
            while (m_node->getLeft() != nullptr) {
                m_node = m_node->getLeft();
            }
            return m_node;
        }
        void remove(K key) {
            Node<K, T>* m_node = search(key, root);
            if (m_node == nullptr) return;
            if (m_node->hasLeft() && m_node->hasRight()) {
                Node<K, T>* leftest {getLeftest(m_node->getRight())};
                m_node->setElem(leftest->getElem());
                m_node->setKey(leftest->getKey());
                remove(leftest);
            }
            else remove(m_node);
            s--;
        }
};

#endif