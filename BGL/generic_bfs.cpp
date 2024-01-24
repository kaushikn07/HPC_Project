#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>

using namespace boost;

int main() {
    // Define the graph type
    typedef adjacency_list<vecS, vecS, undirectedS> Graph;

    // Create a sample graph
    Graph g;
    add_edge(0, 1, g);
    add_edge(1, 2, g);
    add_edge(1, 3, g);
    add_edge(2, 4, g);
    add_edge(3, 5, g);

    // Define properties for BFS algorithm
    std::vector<int> distance(num_vertices(g), -1);
    int start_vertex = 0;

    // Perform BFS
    breadth_first_search(g, start_vertex,
        visitor(make_bfs_visitor(
            record_distances(&distance[0], on_tree_edge())
        ))
    );

    // Display distances
    std::cout << "Distances from vertex " << start_vertex << ":\n";
    for (std::size_t i = 0; i < distance.size(); ++i) {
        std::cout << "Vertex " << i << ": " << distance[i] << '\n';
    }

    return 0;
}
