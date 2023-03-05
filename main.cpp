#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;


// Мы создаем класс `Graph`, который содержит список смежности для каждой вершины.
// Список смежности представляет собой вектор пар, где первый элемент пары - это вершина назначения, а второй элемент - это вес ребра.
template<typename Node, typename Weight>

class Graph
{
public:

    // Метод `addVertex` добавляет новую вершину в список смежности.
    void addVertex(Node node)
    {
        if (adjacencyList.find(node) == adjacencyList.end())
            adjacencyList[node] = vector<pair<Node, Weight>>();
    }

    // Метод `addEdge` добавляет новое ребро между двумя вершинами в списки смежности каждой из них.
    void addEdge(Node from, Node to, Weight weight)
    {
        addVertex(from);
        addVertex(to);
        adjacencyList[from].push_back(make_pair(to, weight));
    }

    // Метод `getNeighbors` возвращает список пар, соответствующих соседям вершины.
    vector<pair<Node, Weight>> getNeighbors(Node node)
    {
        return adjacencyList[node];
    }

    // Дефолтный конструктор
    Graph()
    {
        // инициализация полей
        vertices = 0;
        edges = 0;
    }

    // Конструктор копирования
    Graph(const Graph& other)
    {
        // копируем количество вершин и ребер
        vertices = other.vertices;
        edges = other.edges;

        // копируем список смежности
        adjacencyList.resize(vertices);
        for (int i = 0; i < vertices; i++) {
            adjacencyList[i] = other.adjacencyList[i];
        }
    }

    // Конструктор перемещения
    Graph(Graph&& other) noexcept
    {
        // перемещаем количество вершин и ребер
        vertices = other.vertices;
        edges = other.edges;

        // перемещаем список смежности
        adjacencyList = std::move(other.adjacencyList);

        // обнуляем поля в другом объекте
        other.vertices = 0;
        other.edges = 0;
    }

    // Оператор копирующего присваивания
    Graph& operator=(const Graph& other)
    {
        // проверяем на самоприсваивание
        if (this == &other)
            return *this;

        // копируем количество вершин и ребер
        vertices = other.vertices;
        edges = other.edges;

        // копируем список смежности
        adjacencyList.resize(vertices);
        for (int i = 0; i < vertices; i++)
            adjacencyList[i] = other.adjacencyList[i];

        return *this;
    }

    // Оператор перемещающего присваивания
    Graph& operator=(Graph&& other) noexcept
    {
        // проверяем на самоприсваивание
        if (this == &other)
            return *this;

      // перемещаем количество вершин и ребер
      vertices = other.vertices;
      edges = other.edges;

      // перемещаем список смежности
      adjacencyList = std::move(other.adjacencyList);

      // обнуляем поля в другом объекте
      other.vertices = 0;
      other.edges = 0;

      return *this;
    }

    // Метод empty() проверяет, пуст ли граф. Если граф пуст, то возвращает true, иначе false.
    bool empty() const
    {
        return adjacencyList.empty();
    }


    //Метод size() возвращает количество узлов в графе.
    size_t size() const
    {
        return adjacencyList.size();
    }

    //Метод clear() очищает граф, удаляя все узлы и ребра.
    void clear()
    {
        adjacencyList.clear();
    }

    // Метод swap() обменивает содержимое графа с другим графом.
    void swap(Graph& other) {
        adjacencyList.swap(other.vertices);
    }

    auto begin()
    {
        return adjacencyList.begin();
    }

    auto end()
    {
        return adjacencyList.end();
    }

    auto cbegin() const
    {
        return adjacencyList.cbegin();
    }

    auto cend() const
    {
        return adjacencyList.cend();
    }

    size_t degree_in(Node key)
    {
        size_t count = 0;
        for(auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it)
        {
            for(auto &vec : it->second)
            {
                if(vec.first == key)
                    count++;
            }
        }
        return count;
    }

    size_t degree_out(Node key)
    {
        size_t count = 0;
        for(auto &vec : adjacencyList[key])
        {
            if(vec.first == key)
                count++;
        }
        return count;
    }

    bool loop(Node key)
    {
        for(auto &vec : adjacencyList[key])
        {
            if(vec.first == key)
                return true;
        }
        return false;
    }


private:
    map<Node, vector<pair<Node, Weight>>> adjacencyList; //Мы используем `map` для хранения списков смежности каждой вершины.

    int vertices;
    int edges;
};

template<typename V = int, typename E = int>
void swap(Graph<V, E>& a, Graph<V, E>& b) {
    Graph<V, E> tmp = a;
    a = b;
    b = tmp;
}

int main() {
//    Graph<int, int> graph;
//
//    graph.addEdge(1, 2, 10);
//    graph.addEdge(1, 3, 20);
//    graph.addEdge(2, 3, 30);
//    graph.addEdge(3, 4, 40);
//
//    auto neighbors = graph.getNeighbors(1);
//    for (auto neighbor : neighbors) {
//        cout << neighbor.first << " " << neighbor.second << endl;
//    }

    return 0;
}