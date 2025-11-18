#include <iostream>
#include "Tree.hpp"

int main() {
    Tree<int> T;
    for (int x : {14, 11, 17, 9, 13, 53}) T.insert(x);

    std::cout << "Fringe of T:";
    auto f = fringe(T);
    for (int x : f) std::cout << " " << x;
    std::cout << "\n";

    Tree<int> U;
    for (int x : {11, 9, 13, 14, 17, 53}) U.insert(x);

    std::cout << "Fringe of U:";
    auto g = fringe(U);
    for (int x : g) std::cout << " " << x;
    std::cout << "\n";

    std::cout << "Same fringe? "
              << (hasSameFringe(T,U) ? "yes" : "no")
              << "\n";

    return 0;
}
