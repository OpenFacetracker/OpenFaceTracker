#include <iostream>
#include <console.hpp>

int main(int argc, char* argv[]) {
    oft::Console c = oft::Console(argc, argv);
    c.listener();
    return 0;
}