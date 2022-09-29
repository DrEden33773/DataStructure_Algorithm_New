/**
 * @file AVL.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief an AVL tree
 * @version 0.1
 * @date 2022-09-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

template <typename T>
class AVL {
private:
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
            this->setFloor();
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
    Node*  root = nullptr;
    size_t size = 0;

    Node* maxNodePtr(Node* from = nullptr) {
        if (from == nullptr) {
            from = root;
        }
        Node* res = nullptr;
        if (size == 0) {
            return res;
        }
        res = from;
        while (res != nullptr) {
            if (res->right == nullptr) {
                break;
            }
            res = res->right;
        }
        return res;
    }
    Node* minNodePtr(Node* from = nullptr) {
        if (from == nullptr) {
            from = root;
        }
        Node* res = nullptr;
        if (size == 0) {
            return res;
        }
        res = from;
        while (res != nullptr) {
            if (res->left == nullptr) {
                break;
            }
            res = res->left;
        }
        return res;
    }

public:
    AVL() = default;
    AVL(std::initializer_list<T>&& initList) {
        for (auto element : initList) {
            add(element);
        }
    }
    explicit AVL(std::vector<T>& initList) {
        for (auto element : initList) {
            add(element);
        }
    }

    void add(T& value) { insert(value); }
    void insert(T& value) { }
    void LL_Rotate(Node* from) { }
    void RR_Rotate(Node* from) { }
    void LR_Rotate(Node* from) { }
    void RL_Rotate(Node* from) { }

    bool ifExist(T& inputValue) {
        if (size == 0) {
            return false;
        }
        bool  res  = false;
        Node* curr = root;
        while (curr != nullptr) {
            if (inputValue == curr->value) {
                res = true;
                break; // remember to break!!!!
            } else if (inputValue > curr->value) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        return res;
    }
    Node* getNodeOf(T& value) {
        if (size == 0) {
            return nullptr;
        }
        Node* res  = nullptr;
        Node* curr = root;
        while (curr != nullptr) {
            if (value == curr->value) {
                res = curr;
                break; // remember to break!!!!
            } else if (value > curr->value) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        return res;
    }

    void preOrderOPT(Node* from) {
        if (from == nullptr) {
            return;
        }
        std::cout << from->value << " ";
        preOrderOPT(from->left);
        preOrderOPT(from->right);
    }
    void midOrderOPT(Node* from) {
        if (from == nullptr) {
            return;
        }
        midOrderOPT(from->left);
        std::cout << from->value << " ";
        midOrderOPT(from->right);
    }
    void lateOrderOPT(Node* from) {
        if (from == nullptr) {
            return;
        }
        lateOrderOPT(from->left);
        lateOrderOPT(from->right);
        std::cout << from->value << " ";
    }
    void preOrderEcho() { preOrderOPT(root); }
    void midOrderEcho() { midOrderOPT(root); }
    void lateOrderEcho() { lateOrderOPT(root); }

    void delAllNodes() {
        // BFS-liked delete
        Node*             firstToDel = root;
        std::queue<Node*> BFQ;
        BFQ.push(root);
        while (!BFQ.empty()) {
            Node* toDel = BFQ.front();
            if (toDel->left) {
                BFQ.push(toDel->left);
            }
            if (toDel->right) {
                BFQ.push(toDel->right);
            }
            delete toDel;
            BFQ.pop();
        }
    }
    void delNode(Node* toDel, bool ifUseRightMin = false) {
        bool ifRecursive = false;
        if (toDel->currNodeType == direction::leaf) {
            rmLeaf(toDel);
        } else if (toDel->left != nullptr && toDel->right != nullptr) {
            rmDoubleParent(toDel);
            ifRecursive = true;
        } else {
            rmSingleParent(toDel);
        }

        if (ifRecursive) {
            if (!ifUseRightMin) {
                Node* nextToRemove = maxNodePtr(toDel->left);
                delNode(nextToRemove);
            } else {
                Node* nextToRemove = minNodePtr(toDel->right);
                delNode(nextToRemove, true);
            }
        }
    }
    void remove(T& inputValue, bool ifUseRightMin = false) {
        bool existence = ifExist(inputValue);
        if (!existence) {
            std::cout << "{ " << inputValue << " }"
                      << " doesn't exist, removing will be ignored!"
                      << std::endl;
            return;
        }
        // now you should remove
        Node* toDel = getNodeOf(inputValue);
        delNode(toDel);
    }

    void disconnectParent(Node* toOpt) {
        assert(toOpt != nullptr);
        if (toOpt->parent == nullptr) {
            // toOpt is root
            return;
        }
        if (toOpt->parent->left == toOpt) {
            toOpt->parent->left = nullptr;
        } else {
            toOpt->parent->right = nullptr;
        }
    }
    void delLeaf(Node* toDel) {
        assert(toDel != nullptr);
        disconnectWithParent(toDel);
        delete toDel;
        --size; // important
    }
    void delParent_One_Child(Node* toDel) { // need to judge => if toDel == root
        assert(toDel != nullptr);
        // if toDel == root
        if (toDel->parent == nullptr) {
            if (toDel->left != nullptr) {
                root = toDel->left;
            } else {
                root = toDel->right;
            }
            root->parent = nullptr; // this is a signature!
            delete toDel;
            --size;
            return;
        }

        direction sideToReAttach = direction::uncertain;
        if (toDel == toDel->parent->left) {
            sideToReAttach = direction::left;
        } else {
            sideToReAttach = direction::right;
        }

        Node* reAttached = toDel->parent;
        Node* theChild   = nullptr;

        if (toDel->left == nullptr) {
            theChild = toDel->right;
        } else {
            theChild = toDel->left;
        }

        if (sideToReAttach == direction::right) {
            reAttached->right = theChild;
        } else if (sideToReAttach == direction::left) {
            reAttached->left = theChild;
        } else {
            std::cout << "unexpected error occurs! exit program!"
                      << std::endl;
            exit(-1);
        }
        theChild->parent = reAttached;

        delete toDel;
        --size; // important
    }
    void delParent_Two_Child(Node* toDel, bool ifUseRightMin = false) {
        assert(toDel != nullptr);
        if (!ifUseRightMin) {
            toDel->value = getMax(toDel->left);
        } else {
            toDel->value = getMin(toDel->right);
        }
        // do not --size!
        // because you've just copied a value from other node
    }

    T& getMax(Node* from = nullptr) {
        if (from == nullptr) {
            from = root;
        }
        assert(size != 0);
        Node* curr = from;
        while (curr != nullptr) {
            if (curr->right == nullptr) {
                break;
            }
            curr = curr->right;
        }
        return curr->value;
    }
    T& getMin(Node* from = nullptr) {
        if (from == nullptr) {
            from = root;
        }
        assert(size != 0);
        Node* curr = from;
        while (curr != nullptr) {
            if (curr->left == nullptr) {
                break;
            }
            curr = curr->left;
        }
        return curr->value;
    }
};
