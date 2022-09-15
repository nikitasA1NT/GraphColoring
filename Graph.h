#ifndef GRAPHCOLORING_GRAPH_H
#define GRAPHCOLORING_GRAPH_H

#include <vector>
#include <mutex>

// Graph class with list of nodes
class Graph {
public:
    // Constructor by adjacency list
    Graph(const std::vector<std::vector<int>>& adjacencyList);

    // Destructor
    ~Graph();

    // Minimal chromatic number of the graph
    int ChromaticNumber();

private:
    // Vertex class
    class Vertex {
    private:
        // Vertex id
        int id;

    public:
        // Constructor
        Vertex(int id);

        // Add neighbor
        void addNeighbor(Vertex* neighbor);

        // Getter for id
        int getId() const;

        // Vertex neighbors
        std::vector<Vertex*> neighbors;
    };

    // Graph vertices
    std::vector<Vertex*> vertices;

    // Find vertex by id
    Vertex* findVertex(int id) const;

    // Is equal colors in two vertices
    static bool isEqualColorsInEdge(Vertex* vertex1, Vertex* vertex2, const std::vector<int>& colorsOfVertices) ;

    // All edges have different colors
    bool allEdgesHaveDifferentColors(const std::vector<int>& colorsOfVertices);

    // Мьютекс для функции coloringOptionsEnumeration
    std::mutex mtx;
    // Рекурсивная функция перебора всех возможных раскрасок
    void coloringOptionsEnumeration(int vertexIndex, int colorsAmount, std::vector<int>& colorsOfVertices,
                                    int& result, bool& resultWasFound);
};


#endif //GRAPHCOLORING_GRAPH_H
