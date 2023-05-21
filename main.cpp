#include <iostream>
#include "vector.h"


int main(){

 std::cout << std::endl;

Vector<std::string> v(5, "4");

for(auto i = v.begin(); i != v.end(); ++i) {
    std::cout << *i << ' ';
}

    std::cout << std::endl;

Vector<std::string> v2(v);

for(auto i = v2.begin(); i != v2.end(); ++i) {
    std::cout << *i << ' ';
}

    std::cout << std::endl;

Vector <std::string> v3;

v3 = v2;

for(auto i = v3.begin(); i != v3.end(); ++i) {
    std::cout << *i << ' ';
}
    std::cout << std::endl;

v3.push_back("5");

for(auto i = v3.begin(); i != v3.end(); ++i) {
    std::cout << *i << ' ';
}
    std::cout << std::endl;

    v2.pop_back();
    v2.pop_back();

for(auto i = v2.begin(); i != v2.end(); ++i) {
    std::cout << *i << ' ';
}

    std::cout << std::endl;

    std::cout << v2.empty();

    Vector <std::string> v4;

    std::cout << std::endl;

    std::cout << v4.empty();

    std::cout << std::endl;
    return 0;
}