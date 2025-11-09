#include <iostream>
#include "tlb.hpp"

int main() {
    try {
        std::cout << "Hello TodoListBubble! Trying to init Graphics...\n";
        TLB::instance().init_graphics();
        TLB::instance().window_loop();
    } catch (std::exception& e) {
        std::cout << breset << "ERROR:: " << bred << e.what() << breset << "\n";
        return -1;
    }
    return 0;
}
