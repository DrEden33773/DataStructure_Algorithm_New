/**
 * @file ReverseKNodes.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief Reverse each "K nodes" in a one-direction linked list (len = N >= K)
 *        Attention! => If K > Remaining Nodes (for the first time), then abort the remaining nodes
 *        That means => Directly return the `head` without reversing
 * @version 0.1
 * @date 2022-09-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>

using namespace std;

class ReverseKNodes {
public:
    class node {
        int value;

    public:
        node* next = nullptr;
        node(int& value)
            : value(value) { }
    };

    class RefNode {
    public:
        node* currPtr;
        RefNode* next = nullptr;
        RefNode* prev = nullptr;
        RefNode(node* currRef)
            : currPtr(currRef) { }
        void releaseResources(RefNode* from, RefNode* to) {
            RefNode* toDelete     = to;
            RefNode* nextToDelete = toDelete->prev;
            for (; toDelete != from;) {
                delete toDelete;
                toDelete     = nextToDelete;
                nextToDelete = nextToDelete->prev;
            }
        }
    };

    node* FasterSolution(node* head, int& K) {
        RefNode* refHead = nullptr;
        RefNode* refTail = nullptr;
        // 1. Build Ref-LinkedList
        node* nodeToInit    = head;
        RefNode* tmpRefNode = nullptr;
        bool _ifAbort_      = false;
        for (int cnt = 0; cnt < K - 1; ++cnt) {
            if (!nodeToInit) {
                _ifAbort_ = true;
                break;
            }
            tmpRefNode = new RefNode(nodeToInit);
            if (!refHead) {
                refHead = tmpRefNode;
                refTail = tmpRefNode;
            } else {
                refTail->next    = tmpRefNode;
                tmpRefNode->prev = refTail;
                refTail          = tmpRefNode;
            }
            nodeToInit = nodeToInit->next;
        }
        // 2. Check if need to abort the function
        if (_ifAbort_) {
            tmpRefNode->releaseResources(refHead, refTail);
            return head;
        }
        // 3. if continue, then do it
        node* nextHead     = nodeToInit->next;
        node* returnedHead = refTail->currPtr;
        for (tmpRefNode = refTail; tmpRefNode != refHead;) {
            tmpRefNode->currPtr->next = tmpRefNode->prev->currPtr;
            tmpRefNode                = tmpRefNode->prev;
        }
        refHead->currPtr->next = FasterSolution(nextHead, K);
        tmpRefNode->releaseResources(refHead, refTail);
        return returnedHead;
    };
};