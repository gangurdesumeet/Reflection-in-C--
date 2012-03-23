#include "B.hpp"
#include <iostream>

using namespace std;



void
B::foo(int a, const char *b) {
    cout << "B::foo() called." << endl;
}

int
B::goo(int a, const char *b) {
    cout << "B::goo() called." << endl;
    return 1234;
}
