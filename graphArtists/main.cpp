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

    std::cout << "All artists in graph: ";
    for (unsigned i = 0; i < artists.size() - 1; i++) {
        std::cout << artists[i]->getName() << ", ";
    }
    std::cout << artists[artists.size() - 1] << std::endl;

    std::vector<Edge> songs = g.getAllEdges();
    std::cout << "All songs in graph: ";
    for (unsigned j = 0; j < songs.size() - 1; j++) {
        std::cout << songs[j].getName() << ", ";
    }
    std::cout << songs[songs.size() - 1].getName() << std::endl;
    std::cout << "-+-+-+-+-+-+-+-+-+-+-+-+-+-+" << std::endl;
    g.BFS();

    return 0;
}