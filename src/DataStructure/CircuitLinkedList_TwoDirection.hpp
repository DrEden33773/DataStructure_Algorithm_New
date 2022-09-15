#include <bits/stdc++.h>
using namespace std;

template <typename T>
class CircuitLinkedList_TwoDirection {
private:
    struct node {
        T data;
        node* next = nullptr;
        node* prev = nullptr;
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
            head = tmp;
            tail = tmp;

            tail->next = head;
            head->prev = tail;
        } else {
            tail->next = tmp;
            tmp.prev   = tail;

            tmp.next   = head;
            head->prev = tmp;

            tail = tmp;
        }

        ++num_of_node;
    }

    T pop() {
        assert(num_of_node != 0);

        node& locator = tail->prev;

        locator.next = head;
        head->prev   = locator;

        delete tail;

        tail = locator;

        --num_of_node;
    }
};