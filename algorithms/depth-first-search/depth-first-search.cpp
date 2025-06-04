#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

// Graph representation using adjacency list
class Graph {
private:
    int vertices;
    std::vector<std::vector<int>> adjacencyList;

public:
    // Constructor
    Graph(int v) : vertices(v), adjacencyList(v) {}

    // Add an edge to the graph
    void addEdge(int v, int w) {
        adjacencyList[v].push_back(w);
    }

    // Recursive DFS implementation
    void DFS_recursive(int startVertex) {
        std::vector<bool> visited(vertices, false);
        std::cout << "Recursive DFS starting from vertex " << startVertex << ": ";
        DFS_recursive_util(startVertex, visited);
        std::cout << std::endl;
    }

    // Helper function for recursive DFS
    void DFS_recursive_util(int vertex, std::vector<bool>& visited) {
        // Mark the current vertex as visited
        visited[vertex] = true;
        std::cout << vertex << " ";

        // Recur for all adjacent vertices
        for (int adjacent : adjacencyList[vertex]) {
            if (!visited[adjacent]) {
                DFS_recursive_util(adjacent, visited);
            }
        }
    }

    // Iterative DFS implementation using a stack
    void DFS_iterative(int startVertex) {
        std::vector<bool> visited(vertices, false);
        std::stack<int> stack;

        // Push the starting vertex
        stack.push(startVertex);

        std::cout << "Iterative DFS starting from vertex " << startVertex << ": ";

        while (!stack.empty()) {
            // Pop a vertex from the stack
            int currentVertex = stack.top();
            stack.pop();

            // Skip if already visited
            if (visited[currentVertex]) {
                continue;
            }

            // Print and mark as visited
            std::cout << currentVertex << " ";
            visited[currentVertex] = true;

            // Push all adjacent vertices in reverse order
            // (to match the recursive traversal order)
            for (auto it = adjacencyList[currentVertex].rbegin();
                 it != adjacencyList[currentVertex].rend();
                 ++it) {
                if (!visited[*it]) {
                    stack.push(*it);
                }
            }
        }
        std::cout << std::endl;
    }
};

// Main function to demonstrate the DFS algorithm
int main() {
    // Create a graph
    Graph g(7);  // 7 vertices numbered from 0 to 6

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    // Perform DFS traversals
    g.DFS_recursive(0);
    g.DFS_iterative(0);

    // Create a graph with a cycle
    std::cout << "\nGraph with a cycle:" << std::endl;
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0);
    g2.addEdge(2, 3);

    g2.DFS_recursive(0);
    g2.DFS_iterative(0);

    return 0;
}