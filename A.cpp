#include "A.hpp"
#include <iostream>

using namespace std;



int
A::foo(int a, const char *b) {
    cout << "A::foo() called." << endl;
return 1234;
}
