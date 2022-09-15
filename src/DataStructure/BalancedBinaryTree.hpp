#include <bits/stdc++.h>
using namespace std;

template <typename T>
class BalancedBinaryTree {
private:
    struct node {
        T value;
        size_t which_layer = 0;
        node& prev         = nullptr;
        node& left         = nullptr;
        node& right        = nullptr;
        node(const T& value)
            : value(value) { }
    };
    node& root          = nullptr;
    node& top_leaf      = nullptr;
    size_t num_of_node  = 0;
    size_t num_of_layer = 0;

public:
    BalancedBinaryTree() = default;

    bool query(const T& input) {
        if (num_of_node == 0) {
            throw std::logic_error("No nodes in binary tree ... ");
        }

        // assert(num_of_node > 0);

        bool res  = false;
        node& tmp = root;

        bool if_moved_to_former_left  = false;
        bool if_moved_to_former_right = false;
        int curr_num_of_layer         = 1;
        int passed_num_of_node        = 0;
        for (; passed_num_of_node < num_of_node; ++passed_num_of_node) {
            // judge at first
            if (tmp.value == input) {
                res = true;
                break;
            }
            // move the node then
            if (tmp.left) {
                tmp = tmp.left;
                ++curr_num_of_layer;
                continue;
            } else {
            }
        }
        return res;
    }

    void insert(const T& value) {
        if (num_of_node != 0 && query(value)) {
            return;
        }

        node& curr = new node(value);
        if (root == nullptr) {
            root     = curr;
            top_leaf = curr;
        } else {
            locate_top_leaf();
            if (top_leaf.left) {
                top_leaf.left = curr;
            } else {
                top_leaf.right = curr;
            }
            curr.prev = top_leaf;
        }
        update_num_of_node();
        update_num_of_layer();

        figure_input_node_which_layer(curr);
    }

    inline void locate_top_leaf() {
        if (top_leaf.left && top_leaf.right) { // need to update
            if (top_leaf == root) {
                top_leaf = top_leaf.left;
            } else {
                node& tmp = top_leaf;
                if (tmp.prev.left == tmp) {
                    tmp == tmp.prev.right;
                }
                if (tmp.prev.right == tmp) {
                }
            }
        } else {
            return;
        }
    }

    inline void update_num_of_node() {
        ++num_of_node;
    }

    inline void update_num_of_layer() {
        size_t num_of_node_when_full = (1 << num_of_layer) - 1; // math => 2 ^ num_of_layer - 1
        if (num_of_node_when_full >= num_of_node) {
            return;
        } else {
            ++num_of_layer;
        }
    }

    inline void figure_input_node_which_layer(const node& input) {
        input.which_layer = num_of_layer;
    }
};
