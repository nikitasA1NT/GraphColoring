#include <iostream>
#include "Graph.h"

int main() {
    std::vector<std::vector<int>> adjacencyList1 = {
            { 2, 5, 6 },    // 1 vertex
            { 1, 3, 7 },    // 2
            { 2, 4, 8 },    // 3
            { 3, 5, 9 },    // 4
            { 1, 4, 10 },   // 5
            { 1, 8, 9 },    // 6
            { 2, 9, 10 },   // 7
            { 3, 6, 10 },   // 8
            { 4, 6, 7 },    // 9
            { 5, 7, 8 },    // 10
    };
    Graph graph1(adjacencyList1);
    std::cout << graph1.ChromaticNumber() << std::endl;

    std::vector<std::vector<int>> adjacencyList2 = {
            { 2, 3 },    // 1 vertex
            { 1, 3 },    // 2
            { 1, 2 },    // 3
    };
    Graph graph2(adjacencyList2);
    std::cout << graph2.ChromaticNumber() << std::endl;

    std::vector<std::vector<int>> adjacencyList3 = {
            { 2, 4 },    // 1 vertex
            { 1, 3 },    // 2
            { 2, 4 },    // 3
            { 1, 3 },    // 4
    };
    Graph graph3(adjacencyList3);
    std::cout << graph3.ChromaticNumber() << std::endl;

    return 0;
}
