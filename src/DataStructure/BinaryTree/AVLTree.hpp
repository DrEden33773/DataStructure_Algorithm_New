/// @brief AVL_TREE

#include <bits/stdc++.h>
#include <iterator>

template <typename T>
class AVLTree {
public:
    enum class nodeType : unsigned short {
        root  = 0,
        inner = 1,
        leaf  = 2,
    };

    enum class direction : unsigned short {
        left      = 0,
        right     = 1,
        uncertain = 2,
    };

    struct Node {
        T        value;
        Node*    parent       = nullptr;
        Node*    left         = nullptr;
        Node*    right        = nullptr;
        size_t   floor        = 0;
        nodeType currNodeType = nodeType::leaf;

        Node() = default;

        explicit Node(T& inputValue) {
            this->value = inputValue;
            this->judgeType();
        }

        void judgeType() {
            if (this->parent == nullptr) {
                this->currNodeType = nodeType::root;
            } else if (this->right == nullptr && this->left == nullptr) {
                this->currNodeType = nodeType::leaf;
            } else {
                this->currNodeType = nodeType::inner;
            }
        }

        void setFloor() {
            Node*  currNode      = this;
            size_t currNodeFloor = 0;
            while (currNode->parent != nullptr) {
                ++this->floor;
                currNode = currNode->parent;
            }
        }
    };

private:
};
