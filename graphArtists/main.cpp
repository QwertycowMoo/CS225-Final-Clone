#include "csvParser.h"
#include "graph.h"
#include "edge.h"

#include <iostream>
#include <list>
#include <vector>

int main(int argc, char** argv) {
    unsigned count = 0;
    vector<vector<string>> data = CSVParser::parseCSV("dijkstra_test.csv");

    Graph g = CSVParser::dataToGraph(data);

    std::vector<Vertex*> artists = g.getAllVertices();
    std::cout << "All artists in graph: ";
    for (Vertex* v : artists) {
        if (count == artists.size() - 1) {
            std::cout << v->getName() << ".";
        } else {
            std::cout << v->getName() << ", ";
        }
        count++;
    }
    std::cout << std::endl;
    count = 0;

    std::vector<Edge> songs = g.getAllEdges();
    std::cout << "All songs in graph: ";
    for (Edge e : songs) {
        if (count == songs.size() - 1) {
            std::cout << e.getName() << ".";
        } else {
            std::cout << e.getName() << ", ";
        }
        count++;
    }
    std::cout << std::endl;
    count = 0;

    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << std::endl << "BFS TRAVERSAL: " << std::endl;
    list<Vertex*> traversal = g.BFS();
    for (Vertex* v : traversal) {
        if (count == artists.size() - 1) {
            std::cout << v->getName() << ".";
        } else {
            std::cout << v->getName() << ", ";
        }
        count++;
    }
    std::cout << std::endl;
    count = 0;
    return 0;
}