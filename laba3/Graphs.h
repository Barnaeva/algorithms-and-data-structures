#include "HashTable.h"
#include <functional>

#pragma once

using namespace std;
template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Distance _weight;
        Vertex _vertex;
        Edge(const Distance& weight, const Vertex& vertex) : _weight(weight), _vertex(vertex) {}
    };
private:
    HashTable<Vertex, vector<Edge>> _graph;

    Graph<Vertex, Distance> get_transpose() const {
        Graph<Vertex, Distance> transposed(order());
        for (const auto& v : vertices()) {
            transposed.add_vertex(v);
            for (const auto& e : edges(v)) {
                transposed.add_edge(e._vertex, v, e._weight);
            }
        }
        return transposed;
    }
public:

    Graph(size_t capacity):_graph(capacity){}
    
    bool has_vertex(const Vertex& v) const;
    bool add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v); 
    vector<Vertex> vertices() const;

    void add_edge(const Vertex& from, const Vertex& to,const Distance& d);
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e);
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge(const Edge& e) const;

    vector<Edge> edges(const Vertex& vertex) const;
    vector<Edge> all_edges(const Vertex& vertex) const;

    size_t order() const;
    size_t degree(const Vertex& v) const;
    bool is_connected() const;

    vector<Edge> shortest_path(const Vertex& from,const Vertex& to) const;
    void print_path(const Vertex& start, const vector<Edge>& path) const;

    void walk(const Vertex& start_vertex, function<void(const Vertex&)> action) const;

    Vertex find_optimal_warehouse() const;

};

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_vertex(const Vertex& v) const
{
    if (_graph.search(v)) {
        return true;
    }
    return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::add_vertex(const Vertex& v)
{
    return _graph.insert(v,vector<Edge>());
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_vertex(const Vertex& v)
{
    
    for (const auto& from : vertices()) {
        remove_edge(from, v);
    }
    return _graph.erase(v);
}

template<typename Vertex, typename Distance>
vector<Vertex> Graph<Vertex, Distance>::vertices() const
{
    return _graph.keys();
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::add_edge(const Vertex& from, const Vertex& to, const Distance& d)
{
    if (!has_vertex(from)) add_vertex(from);
    if (!has_vertex(to)) add_vertex(to);

    auto* pair = _graph.search(from);
    pair->value.emplace_back(d, to);
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Vertex& from, const Vertex& to)
{
    auto* from_pair = _graph.search(from);
    if (!from_pair) return false;

    auto& edges = from_pair->value;

    bool removed = false;
    for (auto it = edges.begin(); it != edges.end(); ) {
        if (it->_vertex == to) {
            it = edges.erase(it);
            removed = true;
        }
        else {
            ++it;
        }
    }

    return removed;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::remove_edge(const Edge& e)
{
    for (const auto& vertex : vertices()) {
        auto* edges = _graph.search(vertex);
        if (!edges) continue;
        for (const auto& edge : *edges) {
            if (edge._vertex == e._vertex && edge._weight == e._weight) {
                return true;
            }
        }
    }
    return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Vertex& from, const Vertex& to) const
{
    auto* from_v = _graph.search(from);
    if (!from_v) return false;

    for (const auto& edge : from_v->value) {
        if (edge._vertex == to) {
            return true;
        }
    }
    return false;
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::has_edge(const Edge&e) const
{
    for (const auto& vertex : vertices()) {
        auto* edges = _graph.search(vertex);
        if (!edges) continue;
        for (const auto& edge : *edges) {
            if (edge._vertex == e._vertex && edge._weight == e._weight) {
                return true;
            }
        }
    }
    return false;
}

template<typename Vertex, typename Distance>
vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::edges(const Vertex& vertex) const
{
    vector<Edge> edges_v;
    if (!has_vertex(vertex)) {
        return edges_v;
    }
    auto* vertex_edges = _graph.search(vertex);
    if (vertex_edges) {
        edges_v = vertex_edges->value;
    }
    return edges_v;
}

template<typename Vertex, typename Distance>
vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::all_edges(const Vertex& vertex) const
{
    vector<Edge> all_edges;
    if (!has_vertex(vertex)) {
        return all_edges;
    }

    auto* vertex_edges = _graph.search(vertex);
    if (vertex_edges) {
        all_edges = vertex_edges->value;
    }

    vector<Vertex> all_vertices = _graph.keys();
    for (const Vertex& current_vertex : all_vertices) {

        auto* edges_from_current = _graph.search(current_vertex);
        if (!edges_from_current) continue;

        for (const Edge& edge : edges_from_current->value) {
            if (edge._vertex == vertex) {
                all_edges.push_back(edge);
            }
        }
    }

    return all_edges;
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::order() const
{
    return _graph.keys().size();
}

template<typename Vertex, typename Distance>
size_t Graph<Vertex, Distance>::degree(const Vertex& v) const
{
    return edges(v).size();
}

template<typename Vertex, typename Distance>
bool Graph<Vertex, Distance>::is_connected() const
{
    if (order() == 0) return true;

    const vector<Vertex> all_vertices = vertices();
    const Vertex start = all_vertices.front();

    HashTable<Vertex, bool> visited_forward(order());
    walk(start, [&visited_forward](const Vertex& v) {
        visited_forward.insert_or_assign(v, true);
        });

    for (const auto& v : all_vertices) {
        if (!visited_forward.search(v) || !visited_forward.search(v)->value) {
            return false;
        }
    }

    Graph transposed = get_transpose();
    HashTable<Vertex, bool> visited_backward(order());
    transposed.walk(start, [&visited_backward](const Vertex& v) {
        visited_backward.insert_or_assign(v, true);
        });

    for (const auto& v : all_vertices) {
        if (!visited_backward.search(v) || !visited_backward.search(v)->value) {
            return false;
        }
    }

    return true;
}

template<typename Vertex, typename Distance>
vector<typename Graph<Vertex, Distance>::Edge> Graph<Vertex, Distance>::shortest_path(const Vertex& from, const Vertex& to) const
{   
    if (!has_vertex(from) || !has_vertex(to)) {
        return vector<Edge>();
    }

    HashTable<Vertex, Distance> dist(order());
    HashTable<Vertex, Vertex> prev(order());

    for (const auto& v : vertices()) {
        dist.insert_or_assign(v, numeric_limits<Distance>::max());
    }
    dist.insert_or_assign(from, 0);

    for (size_t i = 1; i < order(); ++i) {
        for (const auto& u : vertices()) {
            for (const auto& e : edges(u)) {
                auto* u_dist = dist.search(u);
                auto* v_dist = dist.search(e._vertex);

                if (u_dist && v_dist &&
                    u_dist->value != numeric_limits<Distance>::max() &&
                    v_dist->value > u_dist->value + e._weight) {
                    dist.insert_or_assign(e._vertex, u_dist->value + e._weight);
                    prev.insert_or_assign(e._vertex, u);
                }
            }
        }
    }

    for (const auto& u : vertices()) {
        for (const auto& e : edges(u)) {
            auto* u_dist = dist.search(u);
            auto* v_dist = dist.search(e._vertex);

            if (u_dist && v_dist &&
                u_dist->value != numeric_limits<Distance>::max() &&
                v_dist->value > u_dist->value + e._weight) {
                return vector<Edge>();
            }
        }
    }

    vector<Edge> path;
    Vertex current = to;
    while (current != from) {
        auto* prev_vertex = prev.search(current);
        if (!prev_vertex) return vector<Edge>();

        bool edge_found = false;
        for (const auto& e : edges(prev_vertex->value)) {
            if (e._vertex == current) {
                path.push_back(e);
                edge_found = true;
                break;
            }
        }

        if (!edge_found) return vector<Edge>();
        current = prev_vertex->value;
    }

    reverse(path.begin(), path.end());
    return path;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::print_path(const Vertex& start, const vector<Edge>& path) const {
    if (path.empty()) {
        cout << "Path from " << start << " doesn't exist or graph contains a negative cycle!" << endl;
        return;
    }

    cout << "Path from " << start;
    Distance total = 0;

    for (const Edge& edge : path) {
        cout << " -> " << edge._vertex << " (" << edge._weight << ")";
        total += edge._weight;
    }

    cout << endl << "Total distance: " << total << endl;
}

template<typename Vertex, typename Distance>
void Graph<Vertex, Distance>::walk(const Vertex& start_vertex, function<void(const Vertex&)> action) const
{
    if (!has_vertex(start_vertex)) return;

    HashTable<Vertex, bool> visited(order());
    vector<Vertex> queue;

    queue.push_back(start_vertex);
    visited.insert(start_vertex, true);

    size_t current_pos = 0;
    while (current_pos < queue.size()) {
        Vertex current = queue[current_pos++];
        action(current);

        auto* edges = _graph.search(current);
        if (!edges) continue;

        for (const Edge& edge : edges->value) {
            if (!visited.search(edge._vertex)) {
                visited.insert(edge._vertex, true);
                queue.push_back(edge._vertex);
            }
        }
    }
}

template<typename Vertex, typename Distance>
Vertex Graph<Vertex, Distance>::find_optimal_warehouse() const
{
    Vertex best_vertex;
    Distance min_avg_distance = numeric_limits<Distance>::max();
    vector<Vertex> all_vertices = vertices();

    for (const Vertex& candidate : all_vertices) {
        Distance total_distance = 0;
        size_t reachable_count = 0;

        for (const Vertex& v : all_vertices) {
            if (v == candidate) continue;

            vector<Edge> path = shortest_path(candidate, v);
            if (!path.empty()) {
                Distance dist = accumulate(path.begin(), path.end(), Distance(0),
                    [](Distance sum, const Edge& e) { return sum + e._weight; });
                total_distance += dist;
                reachable_count++;
            }
        }

        if (reachable_count > 0) {
            Distance avg_distance = total_distance / reachable_count;
            if (avg_distance < min_avg_distance) {
                min_avg_distance = avg_distance;
                best_vertex = candidate;
            }
        }
    }

    return best_vertex;
}
