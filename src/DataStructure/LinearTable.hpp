/**
 * @file LinearTable.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief a simple implementation of linear table (vector)
 * @version 0.1
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class LinearTable {
private:
    unique_ptr<T[]> data = nullptr;
    size_t size          = 0;
    size_t capacity      = initCapacity;
    static bool ifInitted;      // default state <=> false
    static size_t initCapacity; // default value <=> 4

public:
    LinearTable() {
        data      = make_unique<T[]>(capacity);
        ifInitted = true;
    }

    ~LinearTable() {
        ifInitted = false;
    } // unique_ptr will automatically call its mem-drop function

    static void changeCapacity(const size_t& newCapacity) {
        size_t oldInitCapacity = initCapacity;
        initCapacity           = newCapacity;
        printf(
            "Change the initCapacity from {%zu} to {%zu}\n",
            oldInitCapacity,
            initCapacity
        );
        if (ifInitted) {
            printf(
                "Attention! The linear table has been initialized \
earlier than this function being called\n"
            );
            printf(
                "So its best to call the `realloc` function \
with {%zu} as parameter\n",
                newCapacity
            );
        }
        printf("\n");
    }

    void push(const T& input) {
        if (size >= capacity) {
            realloc(2 * capacity);
        }
        data[size++] = input;
    }

    T pop() {
        if (size == 0) {
            throw std::out_of_range("There's no element in the linear table!");
        }
        T res = data[size - 1];
        --size;
        return res;
    }

    [[nodiscard]] size_t getSize() const {
        return size;
    }

    [[nodiscard]] size_t getCapacity() const {
        return capacity;
    }

    void showSize() const {
        printf("Current Size: %zu", getSize());
    }

    void showCapacity() const {
        printf("Current Capacity: %zu", getCapacity());
    }

    void realloc(const size_t& newCapacity) {
        if (newCapacity < size) {
            printf("! size => {%zu}, but newCapacity => {%zu}\n", size, newCapacity);
            printf("To avoid discarding data, `realloc()` function will not be called.\n\n");
            return;
        }
        unique_ptr<T[]> tmpData = make_unique<T[]>(newCapacity);
        for (size_t i = 0; i < size; ++i) {
            tmpData[i] = data[i];
        }
        data.reset(tmpData.release());
        capacity = newCapacity;
    }

    void clear() {
        size = 0;
        printf(
            "Called `clear()` function. Capacity is still {%zu}\n",
            capacity
        );
        printf(
            "It should be noticed that `clear()` is the same as `erase()`"
        );
    }

    void erase() {
        size = 0;
        printf(
            "Called `erase()` function. Capacity is still {%zu}\n",
            capacity
        );
        printf(
            "It should be noticed that `erase()` is the same as `clear()`"
        );
    }

    void printWithFmt() const {
        printf("[ ");
        for (int i = 0; i < size; ++i) {
            printf("%d, ", data[i]);
        }
        printf("\b\b  \b\b");
        printf(" ]");
        printf("\n");
    }

    static void example() {
        printf("\n");
        LinearTable<int>::changeCapacity(4);
        auto Test = make_shared<LinearTable<int>>();
        LinearTable<int>::changeCapacity(2);
        for (int i = 1; i <= 6; ++i) {
            Test->push(i);
        }
        Test->printWithFmt();
        for (int i = 1; i <= 3; ++i) {
            Test->pop();
        }
        for (int i = 1; i <= 2; ++i) {
            Test->push(i);
        }
        Test->printWithFmt();
        printf("\n");
    }
};

template <typename T>
size_t LinearTable<T>::initCapacity = 4;

template <typename T>
bool LinearTable<T>::ifInitted = false;