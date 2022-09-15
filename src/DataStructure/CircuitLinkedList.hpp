#include <bits/stdc++.h>
using namespace std;

template <typename T>
class CircuitLinkedList_TwoDirection {
private:
    struct node {
        T data;
        node* next = nullptr;
        node(const T& data)
            : data(data) { }
    };
    node* head         = nullptr;
    node* tail         = nullptr;
    size_t num_of_node = 0;

public:
    CircuitLinkedList_TwoDirection() = default;

    ~CircuitLinkedList_TwoDirection() {
        for (
            size_t undeleted = num_of_node;
            undeleted > 0;
            --undeleted
        ) {
            pop();
        }
    }

    void add(const T& data) {
        node& tmp = new node(data);

        if (!num_of_node) {
            head       = tmp;
            tail       = tmp;
            tail->next = head;
        } else {
            tail->next = tmp;
            tmp.next   = head;
            tail       = tmp;
        }

        ++num_of_node;
    }

    T pop() {
        assert(num_of_node != 0);

        node& locator = head;
        for (; locator.next != tail; locator = locator.next) { }

        delete tail;

        locator.next = head;
        tail         = locator;

        --num_of_node;
    }
};