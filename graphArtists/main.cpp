#include "csvParser.h"
#include "graph.h"
#include "edge.h"
#include "dijkstra.h"

#include <iostream>
#include <list>
#include <vector>

void printPath(std::vector<Edge*> &path, Graph& g) {
    for (Edge* e : path) {
        pair<string, string> artistIDs = e->getArtistIDs();
        std::cout << e->getName() << " - " << g.findNameFromID(artistIDs.first) << " - " << g.findNameFromID(artistIDs.second) << std::endl;
    }
}

// To find the shortest path between two artists: ./main "SOURCE" "DESTINATION" csv_filepath
// To find a landmark path between two artists: ./main "SOURCE" "LANDMARK" "DESTINATION" csv_filepath

// If an artist doesn't exist, we print out an error message "ARTIST does not exist in csv_filename"
// If the csv file doesn't load in properly, throw an error

int main(int argc, char* argv[]) {
    if (!(argc == 4 || argc == 5)) {
        std::cerr << "Invalid number of command line arguments. Must be 4 or 5.";
        return 1;
    }

    std::string sourceArtist = argv[1];
    std::string landmarkArtist = argc == 5 ? argv[2] : "none";
    std::string destinationArtist = argc == 5 ? argv[3] : argv[2];
    std::string filePath = argc == 5 ? argv[4] : argv[3];

    vector<vector<string>> data = CSVParser::parseCSV(filePath);
    //std::cout << "parsed csv into data" << std::endl;

    Graph g = CSVParser::dataToGraph(data);
    //std::cout << "parsed data into graph" << std::endl;

    // check to see if all input artists are in graph

    if (g.findVertexFromName(sourceArtist) == NULL) {
        std::cerr << sourceArtist << " does not exist in " << filePath << std::endl;
    } else if (landmarkArtist != "none" && g.findVertexFromName(landmarkArtist) == NULL) {
        std::cerr << landmarkArtist << " does not exist in " << filePath << std::endl;
    } else if (g.findVertexFromName(destinationArtist) == NULL) {
        std::cerr << destinationArtist << " does not exist in " << filePath << std::endl;
    }

    if (argc == 4) { // find shortest path between two artists
        Dijkstra dijk;
        std::vector<Edge*> path = dijk.shortestPath(g, g.findVertexFromName(sourceArtist), g.findVertexFromName(destinationArtist));
        std::cout << " " << std::endl;
        std::cout << "Shortest path between " << sourceArtist << " and " << destinationArtist << std::endl;
        printPath(path, g);
    } else {
        // find landmark path between two artists
    }

    return 0;
}