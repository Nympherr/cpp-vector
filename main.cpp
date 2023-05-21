#include <iostream>
#include "vector.h"


int main(){

    Vector<int> vienas;

    vienas.reserve(10);

    vienas.push_back(1);
    vienas.push_back(1);
    vienas.push_back(1);
    vienas.push_back(1);
    vienas.push_back(1);
    vienas.push_back(1);

    std::cout << "Size: " << vienas.size() << "\n";
    std::cout << "Capacity: " << vienas.capacity() << "\n";

    vienas.reserve(4);

    std::cout << "Size: " << vienas.size() << "\n";
    std::cout << "Capacity: " << vienas.capacity() << "\n";

    vienas.resize(15);

    for(int i = 0; i < vienas.size(); i++){
        std::cout << vienas[i] << " ";
    };

    std::cout << "\n";

    vienas.resize(5);

    for(int i = 0; i < vienas.size(); i++){
        std::cout << vienas[i] << " ";
    };

    std::cout << "Size: " << vienas.size() << "\n";

    vienas.clear();
    
    std::cout << "Size: " << vienas.size() << "\n";
    std::cout << "Capacity: " << vienas.capacity() << "\n";


    vienas.push_back(1);
    vienas.push_back(2);
    vienas.push_back(3);
    vienas.push_back(4);
    vienas.push_back(5);
    vienas.push_back(6);

    vienas.print();
    std::cout << "Capacity: " << vienas.capacity() << "\n";

    vienas.erase(1,4);

    vienas.print();
    std::cout << "Capacity: " << vienas.capacity() << "\n";
    return 0;
}