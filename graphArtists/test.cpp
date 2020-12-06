#include "csvParser.h"
#include "graph.h"
#include "edge.h"
#include "dijkstra.h"
#include <iostream>
#include <list>
#include <vector>

void basicGraphTest() {
    vector<vector<string>> data = CSVParser::parseCSV("small_test.csv");

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
        std::cout << e.getArtistIDs().first << " " << e.getName() << " " << e.getArtistIDs().second << std::endl;
    }
    std::cout << std::endl;

}

void dijkstraTest() {
    vector<vector<string>> data = CSVParser::parseCSV("dijkstra_test.csv");
    Graph g = CSVParser::dataToGraph(data);

    std::vector<Vertex*> artists = g.getAllVertices();

    Dijkstra dijk;
    std::vector<Edge*> = dijk.shortestPath(g, *artists[0], *artists[1]);

    artists[0]->print();
    artists[1]->print();

    for (Edge* e : songs) {
        std::cout << e->getArtistIDs().first << " " << e->getName() << " " << e->getArtistIDs().second << std::endl;
    }


}
int main(int argc, char** argv) {
   dijkstraTest();
    return 0;
}

