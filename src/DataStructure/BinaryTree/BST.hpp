/**
 * @file BST.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Binary Search Tree (Only value, doesn't contain key)
 * @version 0.1
 * @date 2022-09-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <cassert>
#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <iostream>

template <typename T>
class BST {
private:
    struct Node {
        T value;
        Node* left   = nullptr;
        Node* right  = nullptr;
        Node* parent = nullptr;

        explicit Node(T&& inputValue) {
            value = inputValue;
        }
    };
    enum class direction {
        left,
        right,
        uncertain,
    };
    enum class ifRoot {
        isRoot,
        nonRoot,
    };
    Node* root        = nullptr;
    size_t numOfNodes = 0;

public:
    void numOfNodes_plus_1() {
        ++numOfNodes;
    }

    void numOfNodes_sub_1() {
        --numOfNodes;
    }

    BST() = default;

    /// @brief this allows => `BST<int> testBST = { 1, 2, 3 }`
    /// @param initList
    BST(std::initializer_list<T>&& initList) {
        for (auto&& element : initList) {
            add(element);
        }
    }

    void insert(T&& inputValue) {
        // 1. init
        Node* toAdd                 = new Node(inputValue);
        Node* attachedTo            = root;
        direction whichSideToAttach = direction::uncertain;

        // 2. set corruption flag
        bool ifCorrupt = false;

        // 3. attach
        if (root == nullptr) {
            root = toAdd;
        } else {
            while (attachedTo != nullptr) {
                if (inputValue == attachedTo->value) {
                    std::cout << "{ " << inputValue << " }"
                              << " has already existed, end inserting!"
                              << std::endl;
                    // REMEMBER! delete the tmp
                    delete toAdd;
                    // now could return
                    return;
                } else if (inputValue > attachedTo->value) {
                    if (attachedTo->right != nullptr) {
                        attachedTo = attachedTo->right;
                    } else {
                        whichSideToAttach = direction::right;
                        break;
                    }
                } else {
                    if (attachedTo->left != nullptr) {
                        attachedTo = attachedTo->left;
                    } else {
                        whichSideToAttach = direction::left;
                        break;
                    }
                }
            }
            // attach
            switch (whichSideToAttach) {
            case direction::left:
                attachedTo->left = toAdd;
                toAdd->parent    = attachedTo;
                break;
            case direction::right:
                attachedTo->right = toAdd;
                toAdd->parent     = attachedTo;
                break;
            case direction::uncertain:
                std::cout << "unexpected error occurs! exit program!" << std::endl;
                exit(-1);
            };
        }

        // 4. upgrade num of nodes
        if (!ifCorrupt) {
            ++numOfNodes;
        }
    }

    void add(T&& inputValue) {
        insert(inputValue);
    }

    bool ifExist(T&& inputValue) {
        if (numOfNodes == 0) {
            return false;
        }

        bool res   = false;
        Node* curr = root;

        while (curr != nullptr) {
            if (inputValue == curr->value) {
                res = true;
            } else if (inputValue > curr->value) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }

        return res;
    }

    Node* search(T&& inputValue) {
        if (numOfNodes == 0) {
            return nullptr;
        }

        Node* res  = nullptr;
        Node* curr = root;

        while (curr != nullptr) {
            if (inputValue == curr->value) {
                res = curr;
            } else if (inputValue > curr->value) {
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }

        return res;
    }

    Node* maxNodePtr(Node* from = nullptr) {
        if (from == nullptr) {
            from = root;
        }

        Node* res = nullptr;
        if (numOfNodes == 0) {
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
        if (numOfNodes == 0) {
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

    T& getMax(Node* from = nullptr) {
        if (from == nullptr) {
            from = root;
        }
        assert(numOfNodes != 0);
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
        assert(numOfNodes != 0);
        Node* curr = from;
        while (curr != nullptr) {
            if (curr->left == nullptr) {
                break;
            }
            curr = curr->left;
        }
        return curr->value;
    }

    /// @brief remove
    /// @param inputValue
    /// @param ifUseRightMin => true, use right sub tree's min && false, use left sub tree's max
    void remove(T&& inputValue, bool ifUseRightMin = false) {
        bool existence = ifExist(inputValue);
        if (!existence) {
            std::cout << "{ " << inputValue << " }"
                      << " doesn't exist, removing will be ignored!"
                      << std::endl;
            return;
        }

        // now you should remove
        Node* toRemove = search(inputValue);

        std::function<void(Node*)> disconnectWithParent = [](Node* toRemove) {
            assert(toRemove != nullptr);
            if (toRemove->parent == nullptr) {
                // toRemove is root
                return;
            }
            if (toRemove->parent->left == toRemove) {
                toRemove->parent->left = nullptr;
            } else {
                toRemove->parent->right = nullptr;
            }
        };

        /// @brief rmLeaf (will delete)
        std::function<void(Node*)> remove0 = [&](Node* toRemove) {
            assert(toRemove != nullptr);

            disconnectWithParent(toRemove);

            delete toRemove;
            --numOfNodes;
        };

        /// @brief rmSingleParent (will delete)
        std::function<void(Node*)> remove1 = [&](Node* toRemove) {
            assert(toRemove != nullptr);

            direction sideToReAttach = direction::uncertain;
            if (toRemove == toRemove->parent->left) {
                sideToReAttach = direction::left;
            } else {
                sideToReAttach = direction::right;
            }

            Node* reAttached = toRemove->parent;
            Node* theChild   = nullptr;

            if (toRemove->left == nullptr) {
                theChild = toRemove->right;
            } else {
                theChild = toRemove->left;
            }

            if (sideToReAttach == direction::right) {
                reAttached->right = theChild;
            } else if (sideToReAttach == direction::left) {
                reAttached->left = theChild;
            } else {
                std::cout << "unexpected error occurs! exit program!" << std::endl;
                exit(-1);
            }
            theChild->parent = reAttached;

            delete toRemove;
            --numOfNodes;
        };

        /// @brief rmDoubleParent (will not delete)
        std::function<void(Node*)> remove2 = [&](Node* toRemove) {
            assert(toRemove != nullptr);

            if (!ifUseRightMin) {
                toRemove->value = getMax(toRemove->left);
            } else {
                toRemove->value = getMin(toRemove->right);
            }
        };

        auto rmLeaf         = remove0;
        auto rmSingleParent = remove1;
        auto rmDoubleParent = remove2;

        bool ifRecursive = false;
        if (toRemove->left == nullptr && toRemove->right == nullptr) {
            rmLeaf(toRemove);
        } else if (toRemove->left != nullptr && toRemove->right != nullptr) {
            rmDoubleParent(toRemove);
            ifRecursive = true;
        } else {
            rmSingleParent(toRemove);
        }

        if (ifRecursive) {
            if (!ifUseRightMin) {
                Node* nextToRemove = maxNodePtr(toRemove->left);
                remove(nextToRemove);
            } else {
                Node* nextToRemove = minNodePtr(toRemove->right);
                remove(nextToRemove, true);
            }
        }
    }

    void preOrderPrint(Node* in) {
        if (in == nullptr) {
            return;
        }
        std::cout << in->value << " ";
        preOrderPrint(in->left);
        preOrderPrint(in->right);
    }

    void midOrderPrint(Node* in) {
        if (in == nullptr) {
            return;
        }
        preOrderPrint(in->left);
        std::cout << in->value << " ";
        preOrderPrint(in->right);
    }

    void laterOrderPrint(Node* in) {
        if (in == nullptr) {
            return;
        }
        preOrderPrint(in->left);
        preOrderPrint(in->right);
        std::cout << in->value << " ";
    }

    void echo() {
        preOrderPrint(root);
    }

    static void example() {
        BST<int> int_BST = { 1, 2, 7, 2, 9, 20, 12 };
        std::cout << "init int_BST with {1,2,7,2,9,20,12}, echo => " << std::endl;
        std::cout << "\t";
        int_BST.echo();
    }
};
