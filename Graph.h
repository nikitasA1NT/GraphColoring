#ifndef GRAPHCOLORING_GRAPH_H
#define GRAPHCOLORING_GRAPH_H

#include <vector>

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
        // Vertex color
        int color;

    public:
        // Constructor
        Vertex(int id, int color);

        // Destructor
        ~Vertex();

        // Add neighbor
        void addNeighbor(Vertex* neighbor);

        // Getter for id
        int getId() const;

        // Getter for color
        int getColor() const;

        // Setter for color
        void setColor(int color);

        // Vertex neighbors
        std::vector<Vertex*> neighbors;
    };

    // Graph vertices
    std::vector<Vertex*> vertices;

    // Find vertex by id
    Vertex* findVertex(int id) const;

    // Is equal colors in two vertices
    bool isEqualColorsInEdge(Vertex* vertex1, Vertex* vertex2) const;

    // All edges have different colors
    bool allEdgesHaveDifferentColors() const;

    void coloringOptionsEnumeration(int vertexIndex, int colorsAmount, int& result, bool& resultWasFound);

    // Reset colors of all vertices
    void resetColors();
};


#endif //GRAPHCOLORING_GRAPH_H
