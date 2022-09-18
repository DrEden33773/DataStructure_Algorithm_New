﻿/**
 * @file BasicBinaryTree.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief BasicBinaryTree => UnBalanced
 * @version 0.1
 * @date 2022-09-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class BasicBinaryTree {
private:
    struct node {
        T value;
        size_t degree = 0;

        node* nextLeft  = nullptr; // nextRight & nextLeft => to the next step
        node* nextRight = nullptr;
        node* left      = nullptr; // right & left => in the same step
        node* right     = nullptr;
        node* prev      = nullptr; // prev => to the previous step

        node(T& inputValue) { value = inputValue; }

        void linkWith(node& beLinked) {
            /// 0. this should not be nullptr
            assert(this != nullptr);

            /// 1. this => beLinked
            if (this->nextRight) {
                this->nextLeft = beLinked;
            } else {
                this->nextRight = beLinked;
            }

            /// 2. beLinked => this
            beLinked->prev = this;

            /// 3. update degree
            ++this->degree;
            ++beLinked.degree;
        }
    };
    node* root        = nullptr;
    node* surface     = root;
    size_t numOfNodes = 0;

public:
    BasicBinaryTree() = default;

    ~BasicBinaryTree() = default;

    auto add(T& value) -> void {
        node* tmp = new node(value);
        if (root) {
            surface->linkWith(tmp);
        } else {
            root = tmp;
        }
        ++numOfNodes;
        updateSurfaceNode();
    }

    auto updateSurfaceNode() -> void {
        if (!surface) {
            surface = root;
        } else {
        }
    }

    auto normalOrderIterate(node* inputNode, bool ifPrint = true) -> void {
        assert(numOfNodes != 0);
        if (ifPrint) {
            cout << inputNode->value << " ";
        }
        if (inputNode == nullptr) {
            return;
        }
        normalOrderIterate(inputNode->left);
        normalOrderIterate(inputNode->right);
    }

    auto findSurfaceNode() -> void { }
};