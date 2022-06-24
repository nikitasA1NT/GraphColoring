#include "Graph.h"

Graph::Vertex::Vertex(int id, int color) {
    this->id = id;
    this->color = color;
}

Graph::Vertex::~Vertex() {
}

int Graph::Vertex::getId() const {
    return id;
}

int Graph::Vertex::getColor() const {
    return color;
}

// Добавить соседей к вершине
void Graph::Vertex::addNeighbor(Graph::Vertex *neighbor) {
    neighbors.push_back(neighbor);
}

// Установка цвета вершины
void Graph::Vertex::setColor(int color) {
    this->color = color;
}

// Конструктор графа по входящему списку смежности
Graph::Graph(const std::vector<std::vector<int>> &adjacencyList) {
    for (int i = 0; i < adjacencyList.size(); i++) {
        Vertex* vertex = new Vertex(i + 1, -1);
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
    for (int colorsAmount = 1; colorsAmount < vertices.size() && !resultFound; ++colorsAmount) {
        // Сброс цветов к значению по умолчанию
        resetColors();

        // Рекурсивная функция перебора всех возможных раскрасок
        coloringOptionsEnumeration(0, colorsAmount, chromaticNumber, resultFound);
    }

    resetColors();

    return chromaticNumber;
}

void Graph::coloringOptionsEnumeration(int vertexIndex, int colorsAmount, int& result, bool& resultFound) {
    // Завершить другие потоки, если результат найден
    if (resultFound) {
        return;
    }

    // Если пройдены все вершины
    if (vertexIndex == vertices.size()) {

        // Проверка, все ли ребра графа имеют на концах разные цвета
        if (allEdgesHaveDifferentColors()) {

            // Критическая секция ////////////////////////////////////
            result = colorsAmount;
            resultFound = true;
            //////////////////////////////////////////////////////////

        }

        return;
    }

    // Рекурсивный перебор раскрасок вершин
    for (int currentColor = 0; currentColor < colorsAmount; ++currentColor) {
        vertices[vertexIndex]->setColor(currentColor);  // Установка цвета
        coloringOptionsEnumeration(vertexIndex + 1, colorsAmount, result, resultFound);  // К следующей вершине
    }
}

// Возвращает правду, если две вершины имеют одинаковые цвета (ребро имеет одинаковые конци)
bool Graph::isEqualColorsInEdge(Graph::Vertex *vertex1, Graph::Vertex *vertex2) const {
    return vertex1->getColor() == vertex2->getColor();
}

// Возвращает правду, все ребра графа имеют разные концы
bool Graph::allEdgesHaveDifferentColors() const {
    // Перебор всех существуеющих ребер в графе
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = 0; j < vertices[i]->neighbors.size(); j++) {
            if (isEqualColorsInEdge(vertices[i], vertices[i]->neighbors[j])) {
                return false;
            }
        }
    }
    return true;
}

// Сброс цветов вершин
void Graph::resetColors() {
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i]->setColor(-1);
    }
}
