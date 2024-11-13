#include <iostream>
using namespace std;

#ifndef __LINKEDLIST__CPP__
#define __LINKEDLIST__CPP__ 

template <typename T>
class NodeList {
    private: 
        T data;
        NodeList<T> *prev, *next;
    public:
        NodeList(): data {0}, prev {nullptr}, next {nullptr} {}
        NodeList(T var, NodeList<T> *m_prev = nullptr, NodeList<T> *m_next = nullptr) {
            data = var;
            prev = m_prev;
            next = m_next;
        }
        NodeList<T> *getNext() { return next; }
        void setNext(NodeList<T> *m_next) { next = m_next; }
        NodeList<T> *getPrev() { return prev; }
        void setPrev(NodeList<T> *m_prev) { prev = m_prev; }
        void setData(T m_data) { data = m_data; }
        T getData() { return data; }
};

template <typename T>
class DoublyList {
    private:
        NodeList<T> *tail, *head;
        int size;
    public:
        DoublyList(): tail {nullptr}, head {nullptr}, size {0} {}
        NodeList<T> *front() { return head; }
        NodeList<T> *back() { return tail; }
        int getSize() { return size; }
        void push_front(T m_data) {
            head = new NodeList<T>(m_data, nullptr, head);
            if (size == 0) tail = head;
            else {
                head->getNext()->setPrev(head);
            }
            size++;
        }
        void push_back(T m_data) {
            if (size == 0) push_front(m_data);
            else {
                tail->setNext(new NodeList<T>(m_data));
                tail->getNext()->setPrev(tail);
                tail = tail->getNext();
                size++;
            }
        }
        void pop_back() {
            if (size == 0) return;
            if (size == 1) {
                delete tail;
                tail = head = nullptr;
            } else {
                tail = tail->getPrev();
                tail->setNext(nullptr);
                delete tail->getNext();
            }
            size--;
        }
        void pop_front() {
            if (size == 0) return;
            if (size == 1) {
                delete head;
                head = tail = nullptr;
            } else {
                head = head->getNext();
                delete head->getPrev();
                head->setPrev(nullptr);
            }
            size--;
        }
        void insert(T m_data, NodeList<T> *pos) {
            NodeList<T> *tmp = new NodeList<T>(m_data);
            tmp->setNext(pos->getNext());
            pos->getNext()->setPrev(tmp);
            tmp->setPrev(pos);
            pos->setNext(tmp);
            size++;
        }
        void erase(NodeList<T> *pos) {
            if (size == 0 || pos == nullptr) return;
            if (pos == head) {
                pop_front();
            } else if (pos == tail) {
                pop_back();
            } else {
                pos->getPrev()->setNext(pos->getNext());
                if (pos->getNext() != nullptr)
                    pos->getNext()->setPrev(pos->getPrev());
                delete pos;
                size--;
            }
        }
};

template <typename T>
class Iterator {
    private: 
        NodeList<T> *it;
    public:
        NodeList<T> *getCur() { return it; }
        Iterator(): it {nullptr} {}
        Iterator(NodeList<T> *m_it): it {m_it} {}
        Iterator<T> operator=(NodeList<T> *tmp){
            it = tmp;
            return *this;
        }
        bool operator!=(NodeList<T>* tmp) {
            return it != tmp;
        }
        Iterator<T> operator++() {
            it = it->getNext();
            return it;
        }
        Iterator<T> operator++(int) {
            Iterator<T> tmp = it;
            it = it->getNext();
            return tmp;
        }
        Iterator<T> operator--() {
            it = it->getPrev();
            return it;
        }
        Iterator<T> operator--(int) {
            Iterator<T> tmp = it;
            it = it->getPrev();
            return tmp;
        }
        T operator*() { return it->getData(); }
};
#endif
