#include <bits/stdc++.h>
using namespace std;

template <typename T>
class LinkedList_single_direction {
private:
    struct node {
        T element;
        node* next = nullptr;
        node* prev = nullptr;
        node(T& element)
            : element(element) { }
    };
    node* head      = nullptr; // head could be unnull
    node* tail      = nullptr;
    size_t node_num = 0;

public:
    LinkedList_single_direction() = default;

    ~LinkedList_single_direction() {
        for (
            int undeleted_node_num = node_num;
            undeleted_node_num > 0;
            --undeleted_node_num
        ) {
            pop();
        }
    }

    void add(T& element) {
        node& curr = node(element);
        if (head == nullptr) {
            head = curr;
            tail = curr;
        } else {
            tail->next = curr;
            curr.prev  = tail;
            tail       = curr;
        }
        ++node_num;
    }

    T pop() {
        if (node_num == 0) {
            throw std::out_of_range("No Elements");
        }
        T Res = tail->element;

        if (node_num == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            node& final_tail = tail->prev;
            delete tail;
            tail       = final_tail;
            tail->next = nullptr;
        }
        --node_num;

        return Res;
    }
};