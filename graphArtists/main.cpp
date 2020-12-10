#include "csvParser.h"
#include "graph.h"
#include "edge.h"
#include "dijkstra.h"
#include "landmark.h"

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>

void printPath(std::vector<Edge*> &path, Graph& g) {
    for (Edge* e : path) {
        pair<string, string> artistIDs = e->getArtistIDs();
        std::cout << e->getName() << " - " << g.findNameFromID(artistIDs.first) << " - " << g.findNameFromID(artistIDs.second) << std::endl;
    }
}

void printAllArtists(Graph& g) {
    std::cout << "All artists in the graph:" << std::endl;

    std::vector<Vertex*> artistPointers = g.getAllVertices();

    std::vector<std::string> artistNames;
    for (Vertex* v : artistPointers) {
        artistNames.push_back(v->getName());
    }

    std::sort(artistNames.begin(), artistNames.end());

    for (unsigned i = 0; i < artistNames.size() - 1; i++) {
        std::cout << artistNames[i] << ", ";
    }
    std::cout << artistNames[artistNames.size() - 1] << std::endl;
}

// To find the shortest path between two artists: ./main "SOURCE" "DESTINATION" csv_filepath
// To find a landmark path between two artists: ./main "SOURCE" "LANDMARK" "DESTINATION" csv_filepath

// If an artist doesn't exist, we print out an error message "ARTIST does not exist in csv_filename"
// If the csv file doesn't load in properly, throw an error

// 3 - ./spotigraph filename -a
// 5 - ./spotigraph artist1 artist2 filepath -path=bfs
// 5 - ./spotigraph artist1 artist2 filepath -path=dijk
// 6 - ./spotigraph artist1 artist2 artist3 filepath -path=landmark

int main(int argc, char* argv[]) {

    if (argc == 3 && std::string(argv[2]).compare("-a") == 0) {
        std::string filePath = argv[1];
        vector<vector<string>> data = CSVParser::parseCSV(filePath);
        Graph g = CSVParser::dataToGraph(data);

        printAllArtists(g);
    }

    if (!(argc == 5 || argc == 6)) {
        std::cerr << "Invalid number of command line arguments. Must be 5 or 6.";
        return 1;
    }

    std::string sourceArtist = argv[1];
    std::string landmarkArtist = argc == 6 ? argv[2] : "none";
    std::string destinationArtist = argc == 6 ? argv[3] : argv[2];
    std::string filePath = argc == 6 ? argv[4] : argv[3];
    std::string pathFlag = argc == 5 ? argv[4] : "none";

    vector<vector<string>> data = CSVParser::parseCSV(filePath);

    Graph g = CSVParser::dataToGraph(data);

    // check to see if all input artists are in graph

    if (g.findVertexFromName(sourceArtist) == NULL) {
        std::cerr << sourceArtist << " does not exist in " << filePath << std::endl;
        return 1;
    } else if (landmarkArtist != "none" && g.findVertexFromName(landmarkArtist) == NULL) {
        std::cerr << landmarkArtist << " does not exist in " << filePath << std::endl;
        return 1;
    } else if (g.findVertexFromName(destinationArtist) == NULL) {
        std::cerr << destinationArtist << " does not exist in " << filePath << std::endl;
        return 1;
    }

    if (argc == 5 && pathFlag == "-path=dijk") { // find shortest path between two artists
        Dijkstra dijk;
        std::vector<Edge*> path = dijk.shortestPath(g, g.findVertexFromName(sourceArtist), g.findVertexFromName(destinationArtist));
        std::cout << " " << std::endl;
        std::cout << "Shortest path between " << sourceArtist << " and " << destinationArtist << std::endl;
        printPath(path, g);
    } else if (argc == 5 && pathFlag == "-path=bfs") {
        
    } else if (argc == 6) { // find landmark path between two artists
        LandmarkPath l;
        std::vector<Edge*> landmarkPath = l.landmarkPath(g, g.findVertexFromName(sourceArtist), g.findVertexFromName(landmarkArtist), g.findVertexFromName(destinationArtist));
        std::cout << " " << std::endl;
        std::cout << "Shortest path between " << sourceArtist << " and " << destinationArtist << " through " << landmarkArtist << std::endl;
        printPath(landmarkPath, g);
    }

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