#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <utility>
#include <fstream>

using namespace std;


// Мы создаем класс `Graph`, который содержит список смежности для каждой вершины.
// Список смежности представляет собой вектор пар, где первый элемент пары - это вершина назначения, а второй элемент - это вес ребра.
template<typename Node, typename Weight>

class Graph
{
public:

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

    void insert_node(pair<Node, Weight> vertice)
    {
        // добавляем новую вершину с пустым списком смежных вершин
        adjacencyList.second.insert(vertice);
        auto pos = adjacencyList.second.at(vertice);
        bool yes_or_no;
        if (pos == NULL)
            yes_or_no = false;
        else
            yes_or_no = true;
        return pos, yes_or_no;
    }

    auto insert_or_assign_node(pair<Node, Weight> vertice)
    {
        int flag = 0;
        bool yes_or_no;

        for(auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it)
        {
            for(auto &vec : it->second)
            {
                for (auto &pair : vec.first)
                {
                    if (pair == vertice)
                    {
                        flag = 1;
                        auto pos = adjacencyList.second.at(pair);
                        yes_or_no = true;
                        return pos, yes_or_no;
                        break;
                    }
                }
            }
        }

        if (flag == 0)
        {
            adjacencyList.second.insert(vertice);
            auto pos = adjacencyList.second.at(vertice);
            if (pos == NULL)
                yes_or_no = false;
            else
                yes_or_no = true;
            return pos, yes_or_no;
        }

        return adjacencyList.second.end(), false;
    }

    auto insert_edge(Node from, Node to, Weight weight)
    {
        adjacencyList[from].push_back(make_pair(to, weight));
        bool yes_or_no;
        auto pos = adjacencyList.second.at(make_pair(from, weight));
        if (pos == NULL)
            yes_or_no = false;
        else
            yes_or_no = true;
        return pos, yes_or_no;
    }

    auto insert_or_assign_edge(Node from, Node to, Weight weight)
    {
        int flag = 0;
        bool yes_or_no;

        for(auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it)
        {
            for (auto &vec: it->second)
            {
                for (auto &pair: vec.first)
                {
                    if (pair == make_pair(from, weight))
                    {
                        flag = 1;
                        auto pos = adjacencyList.second.at(pair);
                        adjacencyList[from].erase(it);
                        insert_edge(from, to, weight);
                        yes_or_no = true;
                        return pos, yes_or_no;
                        break;
                    }
                }
            }
        }

        if (flag == 0)
        {
            adjacencyList[from].push_back(make_pair(to, weight));
            auto pos = adjacencyList.second.at(make_pair(from, weight));
            if (pos == NULL)
                yes_or_no = false;
            else
                yes_or_no = true;
            return pos, yes_or_no;
        }

        return adjacencyList.second.end(), false;
    }

    void clear_edges()
    {
        for (int i = 0; i < adjacencyList.second.size(); i++)
            adjacencyList[i].clear();
    }

    bool clear_edges_go_from(Node key)
    {
        bool yes_or_no;

        for(int i = 0; i < adjacencyList[key].size(); i++)
        {
            int dest = adjacencyList[key][i].first;
            adjacencyList[key].erase(adjacencyList[key].begin() + i);
            i--;
            for(int j = 0; j < adjacencyList[dest].size(); j++)
            {
                if(adjacencyList[dest][j].first == key)
                {
                    adjacencyList[dest].erase(adjacencyList[dest].begin() + j);
                    break;
                }
            }
        }

        if (adjacencyList[key].second == 0)
        {
            yes_or_no = true;
        }
        else
        {
            yes_or_no = false;
        }

        return yes_or_no;
    }

    bool clear_edges_go_to(Node key)
    {
        bool yes_or_no;

        for (int i = 0; i < adjacencyList[key].size(); i++)
        {
            for (int j = 0; j < adjacencyList[i].size(); j++)
            {
                if (adjacencyList[i][j].first == key)
                {
                    adjacencyList[i].erase(adjacencyList[i].begin() + j);
                    j--;
                }
            }
        }

        if (adjacencyList[key].second == 0)
        {
            yes_or_no = true;
        }
        else
        {
            yes_or_no = false;
        }

        return yes_or_no;
    }

    bool erase_node(Node key)
    {
        // Удаление всех ребер, идущих из вершины
        for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++)
        {
            for (auto jt = it->second.begin(); jt != it->second.end(); jt++)
            {
                if (jt->first == key)
                {
                    it->second.erase(jt);
                    break;
                }
            }
        }

        // Удаляем вершину из списка смежности
        adjacencyList.erase(key);

        bool yes_or_no;
        if (adjacencyList[key] == NULL)
            yes_or_no = true;
        else
            yes_or_no = false;
        return yes_or_no;
    }

    bool load_from_file(string path)
    {
        ifstream inFile;
        inFile.open(path);

        if (!inFile)
        {
            cerr << "Unable to open file " << path << endl;
            return false;
        }

        Node from, to;
        Weight weight;

        while (inFile >> from >> to >> weight)
            insert_edge(from, to, weight);

        inFile.close();

        return true;
    }

    void save_to_file(string path)
    {
        ofstream outFile;
        outFile.open(path);

        if (!outFile)
        {
            cerr << "Unable to open file " << path << endl;
            exit(1);
        }

        for (int i = 0; i < adjacencyList.second.size(); i++) {
            for (auto j : adjacencyList[i]) {
                outFile << i << " " << j.first << " " << j.second << endl;
            }
        }

        outFile.close();
    }

private:
    map<Node, vector<pair<Node, Weight>>> adjacencyList; // Мы используем `map` для хранения списков смежности каждой вершины.

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
    return 0;
}