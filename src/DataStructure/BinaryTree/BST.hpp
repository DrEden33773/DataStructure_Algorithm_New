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
        Node* left            = nullptr;
        Node* right           = nullptr;
        unsigned short degree = 0;

        explicit Node(T&& inputValue) {
            value = inputValue;
        }
    };
    Node* root        = nullptr;
    size_t numOfNodes = 0;

public:
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
        Node* toAdd      = new Node(inputValue);
        Node* attachedTo = root;
        enum class direction {
            left,
            right,
            uncertain,
        };
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
                break;
            case direction::right:
                attachedTo->right = toAdd;
                break;
            case direction::uncertain:
                std::cout << "unexpected error occurs! exit program!" << std::endl;
                exit(-1);
            };
            // add degree
            ++attachedTo->degree;
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
            }
        }
    }
};