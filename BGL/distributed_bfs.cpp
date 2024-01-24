#include <iostream>
#include <boost/graph/use_mpi.hpp>
#include <boost/graph/distributed/mpi_process_group.hpp>
#include <boost/graph/distributed/adjacency_list.hpp>
#include <boost/graph/distributed/breadth_first_search.hpp>

int main(int argc, char* argv[]) {
    using namespace boost;

    mpi::environment env(argc, argv);
    mpi::communicator world;

    // Define the graph type
    typedef adjacency_list<vecS, distributedS<mpi_process_group, vecS>, directedS> Graph;

    // Create a sample graph
    Graph g(distributed::mpi_process_group(world));

    if (world.rank() == 0) {
        add_edge(0, 1, g);
        add_edge(1, 2, g);
        add_edge(1, 3, g);
        add_edge(2, 4, g);
        add_edge(3, 5, g);
    }

    // Define properties for BFS algorithm
    std::vector<int> distance(num_vertices(g), -1);
    int start_vertex = 0;

    // Perform distributed BFS
    distributed::breadth_first_search(g, vertex(start_vertex, g),
        visitor(make_bfs_visitor(
            record_distances(&distance[0], on_tree_edge())
        ))
    );

    // Display distances
    if (world.rank() == 0) {
        std::cout << "Distances from vertex " << start_vertex << ":\n";
        for (std::size_t i = 0; i < distance.size(); ++i) {
            std::cout << "Vertex " << i << ": " << distance[i] << '\n';
        }
    }

    return 0;
}
