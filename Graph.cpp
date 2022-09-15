#include "Graph.h"

#include <thread>
#include <iostream>

Graph::Vertex::Vertex(int id) {
    this->id = id;
}

int Graph::Vertex::getId() const {
    return id;
}

// Добавить соседей к вершине
void Graph::Vertex::addNeighbor(Graph::Vertex *neighbor) {
    neighbors.push_back(neighbor);
}

// Конструктор графа по входящему списку смежности
Graph::Graph(const std::vector<std::vector<int>> &adjacencyList) {
    for (int i = 0; i < adjacencyList.size(); i++) {
        Vertex* vertex = new Vertex(i + 1);
        vertices.push_back(vertex);
    }

    for (int i = 0; i < adjacencyList.size(); i++) {
        for (int j = 0; j < adjacencyList[i].size(); j++) {
            vertices[i]->addNeighbor(findVertex(adjacencyList[i][j]));
        }
    }
}

Graph::~Graph() {
    for (int i = 0; i < vertices.size(); i++) {
        delete vertices[i];
    }
}

// Поиск вершины по значению
Graph::Vertex *Graph::findVertex(int id) const {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]->getId() == id) {
            return vertices[i];
        }
    }
    return nullptr;
}

// Функция возвращает хроматическое число графа
int Graph::ChromaticNumber() {
    // Начальное значение количества используемых цветов, если результат не будет найден
    int chromaticNumber = vertices.size();

    // Перебор числа цветов
    bool resultFound = false;
    for (int colorsAmount = 1; colorsAmount < vertices.size(); ++colorsAmount) {

        // Поток, принимающий лямбда-функцию с телом, которое будет выполняться в новом потоке
        std::thread th([&]() {
            // Вектор хранит цвета вершин графа (индекс цвета в векторе соответствует ID вершины)
            std::vector<int> colorsOfVertices(vertices.size(), -1);

            // Рекурсивная функция перебора всех возможных раскрасок
            coloringOptionsEnumeration(0, colorsAmount, colorsOfVertices,
                                       chromaticNumber, resultFound);
        });

        th.join();  // Выполнить все потоки до завершения текущего метода
    }

    return chromaticNumber;
}

void Graph::coloringOptionsEnumeration(int vertexIndex, int colorsAmount, std::vector<int>& colorsOfVertices,
                                       int& result, bool& resultFound) {
    // Завершить другие потоки, если результат найден и текущее количество цветов больше этого найденного результата
    if (resultFound && colorsAmount >= result) {
        return;
    }

    // Если пройдены все вершины
    if (vertexIndex == vertices.size()) {

        // Проверка, все ли ребра графа имеют на концах разные цвета
        if (allEdgesHaveDifferentColors(colorsOfVertices)) {
            // Критическая секция
            mtx.lock();

            result = colorsAmount;
            resultFound = true;
            /*std::cout << "thread: " << std::this_thread::get_id() << " "
            << "current result " << result << std::endl;*/

            mtx.unlock();
        }

        return;
    }

    // Рекурсивный перебор раскрасок вершин
    for (int currentColor = 0; currentColor < colorsAmount; ++currentColor) {
        // Установка цвета
        colorsOfVertices[vertexIndex] = currentColor;
        // К следующей вершине
        coloringOptionsEnumeration(vertexIndex + 1, colorsAmount, colorsOfVertices,
                                   result, resultFound);
    }
}

// Возвращает правду, если две вершины имеют одинаковые цвета (ребро имеет одинаковые конци)
bool Graph::isEqualColorsInEdge(Graph::Vertex *vertex1, Graph::Vertex *vertex2,
                                const std::vector<int>& colorsOfVertices) {
    return colorsOfVertices[vertex1->getId() - 1] == colorsOfVertices[vertex2->getId() - 1];
}

// Возвращает правду, все ребра графа имеют разные концы
bool Graph::allEdgesHaveDifferentColors(const std::vector<int>& colorsOfVertices) {
    // Перебор всех существуеющих ребер в графе
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = 0; j < vertices[i]->neighbors.size(); j++) {
            if (isEqualColorsInEdge(vertices[i], vertices[i]->neighbors[j], colorsOfVertices)) {
                return false;
            }
        }
    }
    return true;
}
