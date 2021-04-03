#include <iostream>
#include <queue>
#include "list.h"


class queue{
private:

    List que;
    Node *head = nullptr;
    Node *tail = nullptr;
    std::size_t size_{0};

public:
    queue() {}
    queue(const queue& other) : size_{other.size_} {
        if (this == &other) {
            return;
        }
        Node *other_help = other.head;
        Node *help = new Node;
        help->prev = nullptr;
        head = help;
        if (size_ == 1) {
            head->next = nullptr;
            head->data = other_help->data;
            tail = head;
            return;
        }
        for (int i = 0; i < other.size_; ++i, other_help = other_help->next) {
            Node *new_node = new Node;
            help->next = new_node;
            new_node->prev = help;
            help->data = other_help->data;
            if (i != other.size_ - 1) help = new_node;
        }
        delete help->next;
        help->next = nullptr;
        tail = help;
    }

    queue(queue&& other) {
        size_ = std::move(other.size_);
        Node *other_help = other.head;
        Node *help = new Node;
        help->prev = nullptr;
        head = help;
        if (size_ == 1) {
            head->next = nullptr;
            head->data = std::move(other_help->data);
            tail = head;
            return;
        }
        for (int i = 0; i < other.size_; ++i, other_help = other_help->next) {
            Node *new_node = new Node;
            help->next = new_node;
            new_node->prev = help;
            help->data = std::move(other_help->data);
            if (i != other.size_ - 1) help = new_node;
        }
        delete help->next;
        help->next = nullptr;
        tail = help;
    }

    void push(const int& elem) {
        Node *nod = new Node;
        nod->data = elem;
        que.plus_end(nod);
        if (head == nullptr) {
            head = nod;
            tail = nod;
        } else {
            tail = nod;
        }
        ++size_;
    }

    int& back() {
        Node *help = head;
        while (help != tail) help = help->next;
        return help->data;
    }

    int& front() {
        return head->data;
    }

    bool empty() const { 
        return head == nullptr;
    }

    void pop() {
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            delete head->prev;
        }
        --size_;
    }

    queue& operator= (const queue& other) {
        if (this == &other) {
            return *this;
        }
        size_ = other.size_;
        if (head != nullptr) {
            while (head != tail) {
                head = head->next;
                delete head->prev;
            }
            delete tail;
        }
        Node *other_help = other.head;
        Node *help = new Node;
        help->prev = nullptr;
        head = help;
        if (size_ == 1) {
            head->next = nullptr;
            head->data = other_help->data;
            tail = head;
            return *this;
        }
        for (int i = 0; i < other.size_; ++i, other_help = other_help->next) {
            Node *new_node = new Node;
            help->next = new_node;
            new_node->prev = help;
            help->data = other_help->data;
            if (i != other.size_ - 1) help = new_node;
        }
        delete help->next;
        help->next = nullptr;
        tail = help;
        return *this;
    }

    queue& operator= (const queue&& other) {
        if (this == &other) {
            return *this;
        }
        size_ = std::move(other.size_);
        if (head != nullptr) {
            while (head != tail) {
                head = head->next;
                delete head->prev;
            }
            delete tail;
        }
        Node *other_help = other.head;
        Node *help = new Node;
        help->prev = nullptr;
        head = help;
        if (size_ == 1) {
            head->next = nullptr;
            head->data = std::move(other_help->data);
            tail = head;
            return *this;
        }
        for (int i = 0; i < other.size_; ++i, other_help = other_help->next) {
            Node *new_node = new Node;
            help->next = new_node;
            new_node->prev = help;
            help->data = std::move(other_help->data);
            if (i != other.size_ - 1) help = new_node;
        }
        delete help->next;
        help->next = nullptr;
        tail = help;
        return *this;
    }

    std::size_t size() const {
        return size_;
    }
};
