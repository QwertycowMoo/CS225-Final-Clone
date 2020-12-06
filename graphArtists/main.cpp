#include "csvParser.h"
#include "graph.h"
#include "edge.h"

#include <iostream>
#include <list>
#include <vector>

int main(int argc, char** argv) {
    vector<vector<string>> data = CSVParser::parseCSV("small_test.csv");

    Graph g = CSVParser::dataToGraph(data);
    //data is currently all strings, will need to
    std::vector<Vertex*> artists = g.getAllVertices();

    std::cout << "All artists in graph:";
    for (Vertex* v : artists) {
        std::cout << v->getName();
    }
    std::cout << std::endl;

    std::vector<Edge> songs = g.getAllEdges();
    std::cout << "All songs in graph:";
    for (Edge e : songs) {
        std::cout << e.getName();
    }
    std::cout << std::endl;

    std::cout << "This ran!" << std::endl;
    return 0;
}