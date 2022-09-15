#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Queue {
private:
    struct node {
        T value;
        node* next = nullptr;
        node(T& value)
            : value(value) { }
    };
    node* front       = nullptr;
    node* back        = nullptr;
    size_t numOfNodes = 0;

public:
    Queue() = default;

    ~Queue() {
        erase();
    }

    void push(T& value) {
        node* toBePushed = new node(value);
        if (!numOfNodes) {
            front = toBePushed;
            back  = toBePushed;
        } else {
            back->next = toBePushed;
            back       = toBePushed;
        }
        ++numOfNodes;
    }

    T pop() {
        assert(numOfNodes != 0);
        T toBeReturned = front->value;
        node* newFront = front->next;
        delete front;
        front = newFront;
        --numOfNodes;
    }

    void erase() {
        assert(numOfNodes != 0);
        for (int remaining = numOfNodes; remaining > 0; --remaining) {
            pop();
        }
    }
};