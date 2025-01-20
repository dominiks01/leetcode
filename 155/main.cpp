#include <limits.h>

#include <cstddef>
#include <iostream>
#include <vector>

class MinStack {
   public:
    MinStack() {
        size = {0};
        minValue = {0};
    }

    void push(int val) {
        if (size == 0) {
            minValue = val;
            items[size++] = val;
            return;
        }

        if (val < minValue) {
            items[size++] = 2 * val - minValue;
            minValue = val;
        } else {
            items[size++] = val;
        }

        items[size++] = val;
    }

    void pop() {
        if (items[size - 1] < minValue) {
            minValue = 2 * minValue - items[size - 1];
            items[size - 1] = 0;
            size--;
        }
    }

    int top() {
        return (items[size - 1] < minValue) ? minValue : items[size - 1];
    }

    int getMin() { return minValue; }

   private:
    size_t size{0};
    int items[30000] = {};
    int minValue{INT_MAX};
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */