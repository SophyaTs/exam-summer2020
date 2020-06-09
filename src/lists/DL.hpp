#pragma once

#include <cassert>

namespace exam::list {

template<typename T>
class DL {
public:
    struct Node {
        T value;
        int index;
        Node* next;
        Node* prev;

        Node():next(nullptr), prev(nullptr), index(0) {}
        Node(const T& value, const int index = 0) :value{value}, next(nullptr), prev(nullptr), index{ index } {}
    };

    class Iterator {
    public:
        Iterator():_node(nullptr){}
        Iterator(Node* node):_node(node){}

        T operator*() {
            assert(_node && "Iterator for nullptr doesn't have data");
            return _node->value;
        }

        bool operator!=(const Iterator &other) {
            return *_node != other._node;
        }

        bool operator<(const Iterator &other) {
            return _node->index < other._node->index;
        }

        Iterator &operator--() {
            if (_node)
                _node = _node->prev;
            return *this;
        }

        Iterator &operator++() {
            if(_node)
                _node = _node->next;
            return *this;
        }

        bool empty() const noexcept {
            return !_node;
        }
    private:
        Node* _node;
    };
public:
    DL():_start(nullptr),_size(0){}

    void insert(const T& data) {
        ++_size;
        Node* node = new Node(data, _size - 1);

        if (_start) {
            Node* ptr = _start;
            while (ptr->next)
                ptr = ptr->next;
            ptr->next = node;
            node->prev = ptr;
            _end = node;
        }
        else {
            _start = node;
            _end = node;
        }
    }

    void remove(const int index) {
        if (_size && index>0 && index<_size) {
            Node* ptr = _start;
            while (index < ptr->index)
                ptr = ptr->next;

            if (ptr->prev)
                ptr->prev->next = ptr->next;
            if (ptr->next)
                ptr->next->prev = ptr->prev;
            else
                _end = ptr->prev;
            
            if (ptr == _start)
                _start = ptr;

            delete ptr;
        }
    }

    Iterator search(const T data) {
        Node* ptr = _start;
        while (ptr) {
            if (ptr->value == data)
                return Iterator(ptr);
            ptr = ptr->parent;
        }
        return Iterator();
    }

    Iterator begin() {
        return Iterator(_start);
    }

    Iterator end() {
        return Iterator(_end);
    }
private:
    Node* _start;
    Node* _end;
    int _size;
};

}