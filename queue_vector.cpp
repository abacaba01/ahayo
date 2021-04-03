#include <iostream>
#include <queue>
#include "vector.h"


template <class T>
class queue{
private:

    vector<T> que;
    std::size_t head{0};
    int end{-1};

public:
    queue() {}

    queue(const queue& x) : end{x.end}, head{x.head} {
        que = x.que;
    }
    void push(const T& elem) {
        que.push_back(elem);
        ++end;
    }

    T& back() {
        return que[end];
    }

    T& front() {
        return que[head];
    }

    bool empty() { 
        return que.empty();
    }

    void pop() {
        ++head;
    }
    std::size_t size() const {
        return end < head ? 0 : end - head + 1;
    }
};
