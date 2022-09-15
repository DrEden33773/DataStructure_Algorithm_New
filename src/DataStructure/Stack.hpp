#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Stack {
private:
    struct node {
        T value;
        node* next = nullptr;
        node(T& value)
            : value(value) { }
    };
    node* top         = nullptr;
    node* bottom      = nullptr;
    size_t numOfNodes = 0;

public:
    Stack() = default;

    ~Stack() {
        erase();
    }

    void push(T& value) {
        node* toBePushed = new node(value);
        if (!numOfNodes) {
            top    = toBePushed;
            bottom = toBePushed;
        } else {
            toBePushed->next = top;
            top              = toBePushed;
        }
        ++numOfNodes;
    }

    T pop() {
        assert(numOfNodes != 0);
        T toBeReturned = top->value;
        node* newTop   = top->next;
        delete top;
        top = newTop;
        --numOfNodes;
    }

    void erase() {
        assert(numOfNodes != 0);
        for (int remaining = numOfNodes; remaining > 0; --remaining) {
            pop();
        }
    }
};