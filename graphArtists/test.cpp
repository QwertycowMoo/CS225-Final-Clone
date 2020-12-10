#include "csvParser.h"
#include "graph.h"
#include "edge.h"
#include "dijkstra.h"
#include "landmark.h"
#include <iostream>
#include <list>
#include <vector>
#include <fstream>

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

void bfsTest1(string filename) {
    vector<vector<string>> data = CSVParser::parseCSV(filename);
    // initialization messages
    std::cout << "done!" << std::endl;
    std::cout << "Turning csv into graph...";
    Graph g = CSVParser::dataToGraph(data);
    std::cout << "done!" << std::endl;

    // test number 1: 6 degree 1s, 1 degree 2
    std::list<string> expected = {"Jacob Collier", "Kiana Ledé", "Tori Kelly", "Rapsody", "Mahalia", "Jules Buckley", "Ty Dolla $ign", "Laura Mvula"};
    std::list<Vertex*> output = g.BFS("Jacob Collier");
    std::cout << "EXPECTED | OUTPUT" << std::endl;
    while (!output.empty()) {
        // expected string
        std::string e = expected.front();
        expected.pop_front();
        // output string
        std::string o = output.front()->getName();
        output.pop_front();
        // test output 
        std::cout << e << " | " << o << std::endl;
    }
}

void bfsTest2(string filename) {
    vector<vector<string>> data = CSVParser::parseCSV(filename);
    // initialization messages
    std::cout << std::endl << std::endl << std::endl << "done!" << std::endl;
    std::cout << "Turning csv into graph...";
    Graph g = CSVParser::dataToGraph(data);
    std::cout << "done!" << std::endl;

    // output
    std::list<Vertex*> output = g.BFS("Daniel Caesar");
    if (output.size() < 1000) {
        while (!output.empty()) {

            for (int i = 0; i < 10; i++) {
                // output string
                std::string o = output.front()->getName();
                output.pop_front();
                // test output 
                std::cout << o << ", ";
                if (output.empty()) {break;}
            }
            std::cout << std::endl;
        }
    } else {
        std::ofstream myFile("bfs.txt");
        while (!output.empty()) {
            std::string o = output.front()->getName();
            output.pop_front();
            myFile << o << std::endl;
        }
        myFile.close();
    }
}

/**
 * MAIN FUNCTION FOR RUNNING TESTS!
 * @return prints data relevant to the test used.
 */ 
int main(int argc, char** argv) {
    //landmarkTest("artist_connections.csv");
    //bfsTest1("bfs_test1.csv");
    bfsTest2("artist_connections.csv");
    return 0;
}