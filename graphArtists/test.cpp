#include "csvParser.h"
#include "graph.h"
#include "edge.h"
#include "dijkstra.h"
#include "landmark.h"
#include <iostream>
#include <list>
#include <vector>

void basicGraphTest(string filename) {
    vector<vector<string>> data = CSVParser::parseCSV(filename);

    //Expected Output for small_test.csv
    Graph g = CSVParser::dataToGraph(data);
    //data is currently all strings, will need to
    std::vector<Vertex*> artists = g.getAllVertices();

    /**
    Expected output:
    Kiana Ledé
    Ty Dolla $ign
    Mahalia
    Jacob Collier
    **/
    std::cout << "All artists in graph:" << std::endl;
    for (Vertex* v : artists) {
        std::cout << v->getName() << std::endl;
    }
    std::cout << std::endl;


    /**
    Expected output:
    0QWrMNukfcVOmgEU0FEDyD All I Need (with Mahalia & Ty Dolla $ign) 16rCzZOMQX7P8Kmn5YKexI
    0QWrMNukfcVOmgEU0FEDyD All I Need (with Mahalia & Ty Dolla $ign) 7c0XG5cIJTrrAgEC3ULPiq
    16rCzZOMQX7P8Kmn5YKexI All I Need (with Mahalia & Ty Dolla $ign) 7c0XG5cIJTrrAgEC3ULPiq
    7c0XG5cIJTrrAgEC3ULPiq Alone for Christmas (feat. Kiana Ledé) - from Still Home For The Holidays (An R&B Christmas Album) 7jZMxhsB8djyIbYmoiJSTs
    0QWrMNukfcVOmgEU0FEDyD In Too Deep (feat. Kiana Ledé) – Acoustic 7jZMxhsB8djyIbYmoiJSTs
    **/
    std::vector<Edge> songs = g.getAllEdges();
    std::cout << "All songs in graph:" << std::endl;
    for (Edge e : songs) {
        std::cout << e.getArtistIDs().first << " " << e.getName() << " " << e.getArtistIDs().second << " " << e.getLength() << std::endl;
    }
    std::cout << std::endl;

}

void dijkstraTest(string filename) {
    std::cout << "parsing csv...";
    vector<vector<string>> data = CSVParser::parseCSV(filename);

    std::cout << "done!" << std::endl;
    std::cout << "Turning csv into graph...";
    Graph g = CSVParser::dataToGraph(data);
    std::cout << "done!" << std::endl;


    std::vector<Vertex*> artists = g.getAllVertices();

    Dijkstra dijk;
    std::cout << "performing Dijkstra's...";
    
    //finds path between Ariana Grande and Jon Bellion
    std::vector<Edge*> path = dijk.shortestPath(g, g.findVertex("66CXWjxzNUsdJxJ2JdwvnR"), g.findVertex("50JJSqHUf2RQ9xsHs0KMHg"));
    std::cout << "done!" << std::endl << std::endl;

    g.findVertex("66CXWjxzNUsdJxJ2JdwvnR")->print();
    std::cout << "to" << std::endl;
    g.findVertex("50JJSqHUf2RQ9xsHs0KMHg")->print();
    for (Edge* e : path) {
        std::cout << g.findVertex(e->getArtistIDs().first)->getName() << " | " << e->getId() << " | " << e->getName() << " | " << g.findVertex(e->getArtistIDs().second)->getName() << std::endl;
    }


}

void landmarkTest(string filename) {
      std::cout << "parsing csv...";
    vector<vector<string>> data = CSVParser::parseCSV(filename);

    std::cout << "done!" << std::endl;
    std::cout << "Turning csv into graph...";
    Graph g = CSVParser::dataToGraph(data);
    std::cout << "done!" << std::endl;

    LandmarkPath l;
    std::cout << "performing landmark path:" << std::endl;
    //                                          Ariana Grande                          Jacob Collier                            Jon Bellion
    std::vector<Edge*> path = l.landmarkPath(g, g.findVertex("66CXWjxzNUsdJxJ2JdwvnR"), g.findVertex("0QWrMNukfcVOmgEU0FEDyD"), g.findVertex("50JJSqHUf2RQ9xsHs0KMHg"));


    g.findVertex("66CXWjxzNUsdJxJ2JdwvnR")->print();
    std::cout << "to" << std::endl;
    g.findVertex("0QWrMNukfcVOmgEU0FEDyD")->print();
    std::cout << "to" << std::endl;
    g.findVertex("50JJSqHUf2RQ9xsHs0KMHg")->print();

    for (Edge* e : path) {
        std::cout << g.findVertex(e->getArtistIDs().first)->getName() << " | " << e->getId() << " | " << e->getName() << " | " << g.findVertex(e->getArtistIDs().second)->getName() << std::endl;
    }
}
int main(int argc, char** argv) {
    landmarkTest("artist_connections.csv");
    return 0;
}

