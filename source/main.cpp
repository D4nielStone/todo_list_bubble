#include <iostream>
#include "tlb.hpp"

int main() {
    try {
        std::cout << "Hello TodoListBubble! Trying to init the graphical library...\n";
        TLB::initGraphics();
    } catch (std::exception& e) {
        std::cout << breset << "ERROR" << bred << e.what();
        return -1;
    }
    return 0;
}
