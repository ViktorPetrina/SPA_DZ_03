#include <vector>
#include <list>
#include <limits>
#include <set>
#include <utility>
#include <algorithm>
#include <chrono>
#include <thread>

typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();

struct neighbor
{
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor>> adjacency_list_t;

adjacency_list_t CreateAdjacencyList(const std::vector<std::vector<int>>& field)
{
    int rows = field.size();
    int cols = field[0].size();

    adjacency_list_t adjacency_list(rows * cols);
    auto isValidCell = [&](int row, int col) {
        return (row >= 0 && row < rows && col >= 0 && col < cols && field[row][col] != -1);
    };

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (field[row][col] == -1) {
                continue; 
            }

            static const int dx[] = { -1, 0, 1, 0 };  
            static const int dy[] = { 0, -1, 0, 1 };

            for (int k = 0; k < 4; ++k) {
                int newRow = row + dx[k];
                int newCol = col + dy[k];

                if (isValidCell(newRow, newCol)) {
                    vertex_t source = row * cols + col;
                    vertex_t target = newRow * cols + newCol;
                    weight_t weight = 1.0;

                    adjacency_list[source].push_back(neighbor(target, weight));
                }
            }
        }
    }

    return adjacency_list;
}

void DijkstraComputePaths(vertex_t source, const adjacency_list_t& adjacency_list,
    std::vector<weight_t>& min_distance, std::vector<vertex_t>& previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    std::set<std::pair<weight_t, vertex_t>> vertex_queue;
    vertex_queue.insert(std::make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        // Visit each edge exiting u
        const std::vector<neighbor>& neighbors = adjacency_list[u];
        for (const auto& neighbor : neighbors)
        {
            vertex_t v = neighbor.target;
            weight_t weight = neighbor.weight;
            weight_t distance_through_u = dist + weight;

            if (distance_through_u < min_distance[v]) {
                vertex_queue.erase(std::make_pair(min_distance[v], v));

                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.insert(std::make_pair(min_distance[v], v));
            }
        }
    }
}

std::list<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex, const std::vector<vertex_t>& previous)
{
    std::list<vertex_t> path;
    for (; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}

void PrintField(const std::vector<std::vector<int>>& field, int currentRow, int currentCol)
{
    for (size_t i = 0; i < field.size(); ++i) {
        for (size_t j = 0; j < field[i].size(); ++j) {
            if (field[i][j] == -1) {
                std::cout << '#';
            }
            else if (i == currentRow && j == currentCol) {
                std::cout << 'O';
            }
            else {
                std::cout << '-';
            }
        }
        std::cout << std::endl;
    }
}