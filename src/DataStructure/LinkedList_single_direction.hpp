#include <bits/stdc++.h>
using namespace std;

template <typename T>
class LinkedList_single_direction {
private:
    struct node {
        T element;
        node* next = nullptr;
        node(T& element)
            : element(element) { }
    };
    node* head      = nullptr; // head is always a nullptr
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
        if (node_num == 0) {
            head->next = curr;
            tail       = curr;
        } else {
            tail->next = curr;
            tail       = curr;
        }
        ++node_num;
    }

    T pop() {
        if (node_num == 0) {
            throw std::out_of_range("No Elements");
        }
        T Res = tail->element;

        // locate tail node
        node& tmp = head;
        for (; tmp.next != tail; tmp = tmp.next) { }
        // delete tail node
        delete tail;
        // redirect tail node
        tail = tmp;
        // update node_num
        --node_num;

        return Res;
    }

    static void example() {
        LinkedList_single_direction<int> Test;
    }
};