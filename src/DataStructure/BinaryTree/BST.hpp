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
#include <ostream>
#include <queue>

template <typename T>
class BST {
private:
    struct Node {
        T     value;
        Node* left   = nullptr;
        Node* right  = nullptr;
        Node* parent = nullptr;

        explicit Node(T& inputValue) { value = inputValue; }
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
    Node*  root       = nullptr;
    size_t numOfNodes = 0;

public:
    void numOfNodes_plus_1() { ++numOfNodes; }

    void numOfNodes_sub_1() { --numOfNodes; }

    BST() = default;

    /// @brief this allows => `BST<int> testBST = { 1, 2, 3 }`
    /// @param initList
    BST(std::initializer_list<T>&& initList) {
        for (auto element : initList) {
            add(element);
        }
    }

    explicit BST(std::vector<T>& initList) {
        for (auto element : initList) {
            add(element);
        }
    }

    ~BST() {
        delAllNode();
    }

    void insert(T& inputValue) {
        // 1. init
        Node*     toAdd             = new Node(inputValue);
        Node*     attachedTo        = root;
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
                std::cout << "unexpected error occurs! exit program!"
                          << std::endl;
                exit(-1);
            };
        }

        // 4. upgrade num of nodes
        if (!ifCorrupt) {
            ++numOfNodes;
        }
    }

    void add(T& inputValue) { insert(inputValue); }

    bool ifExist(T& inputValue) {
        if (numOfNodes == 0) {
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

    Node* search(T& inputValue) {
        if (numOfNodes == 0) {
            return nullptr;
        }

        Node* res  = nullptr;
        Node* curr = root;

        while (curr != nullptr) {
            if (inputValue == curr->value) {
                res = curr;
                break; // remember to break!!!!
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

    void delNode(Node* toDel, bool ifUseRightMin = false) {
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
            // need to judge => if toRemove == root

            assert(toRemove != nullptr);

            // if toRemove == root
            if (toRemove->parent == nullptr) {
                if (toRemove->left != nullptr) {
                    root = toRemove->left;
                } else {
                    root = toRemove->right;
                }
                root->parent = nullptr; // this is a signature!
                delete toRemove;
                --numOfNodes;
                return;
            }

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
                std::cout << "unexpected error occurs! exit program!"
                          << std::endl;
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
        if (toDel->left == nullptr && toDel->right == nullptr) {
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
    void remove(T inputValue, bool ifUseRightMin = false) {
        bool existence = ifExist(inputValue);
        if (!existence) {
            std::cout << "{ " << inputValue << " }"
                      << " doesn't exist, removing will be ignored!"
                      << std::endl;
            return;
        }

        // now you should remove
        Node* toDel = search(inputValue);

        delNode(toDel);
    }

    void preOPT(Node* in) {
        if (in == nullptr) {
            return;
        }
        std::cout << in->value << " ";
        preOPT(in->left);
        preOPT(in->right);
    }
    void preOrderPrint() {
        preOPT(root);
    }

    void midOPT(Node* in) {
        if (in == nullptr) {
            return;
        }
        midOPT(in->left);
        std::cout << in->value << " ";
        midOPT(in->right);
    }
    void midOrderPrint() {
        midOPT(root);
    }

    void lateOPT(Node* in) {
        if (in == nullptr) {
            return;
        }
        lateOPT(in->left);
        lateOPT(in->right);
        std::cout << in->value << " ";
    }
    void laterOrderPrint() {
        lateOPT(root);
    }

    void echo() {
        midOrderPrint();
        std::cout << std::endl;
    }

    void delAllNode() {
        // BFS-liked delete
        Node* firstToDel = root;

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

    static void example() {
        BST<int> int_BST = { 1, 2, 7, 9, 20, 12 };
        std::cout << "init int_BST with {1,2,7,9,20,12}, echo => ";
        int_BST.echo();
        //
        int_BST.remove(1);
        int_BST.echo();
        int_BST.remove(20);
        int_BST.echo();
        int_BST.remove(7);
        int_BST.echo();
        // maybe okay

        std::cout << std::endl;

        // randomly init
        std::cout << "Next, a `vector` with 12 elements will be generated." << std::endl;
        std::cout << "Each element is a random int between 1 and 10000 (contain)." << std::endl;
        std::cout << std::endl;

        std::vector<int> toInit;
        toInit.reserve(14);
        srand(time(nullptr));
        for (int i = 0; i < 12; ++i) {
            int toInput = rand() % 10000 - 1;
            toInit.emplace_back(toInput);
        }

        std::cout << "Here's the randomly generated initList => " << std::endl;
        for (auto&& elem : toInit) {
            std::cout << elem << " ";
        }
        std::cout << std::endl
                  << std::endl;

        BST<int> int_BST_final(toInit);
        int_BST_final.echo();
        for (int p = 2; p <= 5; ++p) {
            int_BST_final.remove(toInit[p]);
            int_BST_final.echo();
        }
    }
};
