#include <iostream>
#include <vector>
#include "Graphs.h"

using namespace std;


int main() {
    try {
        cout << "=== Creating graph with capacity 10 ===" << endl;
        Graph<string, double> g(10);

        vector<string> vertices = { "A", "B", "C", "D" };
        for (const auto& v : vertices) {
            g.add_vertex(v);
            cout << "Added vertex: " << v << endl;
        }

        cout << "\n=== Adding edges ===" << endl;
        g.add_edge("A", "B", 2.0);
        g.add_edge("B", "C", 3.0);
        g.add_edge("C", "D", -19.0);
        g.add_edge("D", "A", 4.0);
        g.add_edge("A", "C", -70.0);
        g.add_edge("B", "D", 5.0);
        cout << "Added 6 edges between vertices" << endl;

        cout << "\n=== Checking vertices and edges ===" << endl;
        cout << "Has vertex A: " << boolalpha << g.has_vertex("A") << endl;
        cout << "Has edge A->B: " << g.has_edge("A", "B") << endl;
        cout << "Has edge B->A: " << g.has_edge("B", "A") << endl;

        cout << "\n=== All vertices (" << g.order() << ") ===" << endl;
        for (const auto& v : g.vertices()) {
            cout << v << " ";
        }
        cout << endl;

        cout << "\n=== Edges for each vertex ===" << endl;
        for (const auto& v : g.vertices()) {
            cout << "Edges from " << v << ": ";
            for (const auto& e : g.edges(v)) {
                cout << e._vertex << "(" << e._weight << ") ";
            }
            cout << endl;
        }

        cout << "\n=== BFS traversal from A ===" << endl;
        g.walk("A", [](const string& v) {
            cout << "Visited: " << v << endl;
            });

        cout << "\n=== Collecting vertices to vector ===" << endl;
        vector<string> visited_vertices;
        g.walk("A", [&visited_vertices](const string& v) {
            visited_vertices.push_back(v);
            });
        cout << "Visited vertices: ";
        for (const auto& v : visited_vertices) {
            cout << v << " ";
        }
        cout << endl;

        cout << "\n=== Shortest path from A to D ===" << endl;
        auto path = g.shortest_path("A", "D");
        g.print_path("A", path);

        cout << "\n=== Connectivity check ===" << endl;
        cout << "Graph is connected: " << g.is_connected() << endl;

        cout << "\n=== Adding isolated vertex E ===" << endl;
        g.add_vertex("E");
        cout << "Graph is connected: " << g.is_connected() << endl;

        cout << "\n=== Finding optimal warehouse ===" << endl;
        string warehouse = g.find_optimal_warehouse();
        cout << "Best warehouse location: " << warehouse << endl;

        cout << "\n=== Removing edge A->C ===" << endl;
        g.remove_edge("A", "C");
        path = g.shortest_path("A", "D");
        g.print_path("A", path);

        cout << "\n=== Removing vertex B ===" << endl;
        g.remove_vertex("B");
        cout << "Now vertices are: ";
        for (const auto& v : g.vertices()) {
            cout << v << " ";
        }
        cout << endl;

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}