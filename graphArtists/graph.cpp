
#include "graph.h"

#include <unordered_map>
#include <iostream>

Graph::Graph() {

}

Graph::~Graph() {
    for (unordered_map<string, Vertex*>::iterator it = vertexList.begin(); it != vertexList.end(); ++it) {
        delete it->second;
    }

    for (Edge* e : edgeList) {
        delete e;
    }
}

/**
 * Checks the vertex list for vertexes with the current artist. If so, returns a reference to that vertex.
 * Otherwise, it will create a new vertex and add it to the vertex list.
 */
Vertex* Graph::insertVertex(const string& id, const string& artistName) {
    if (vertexList.find(id) != vertexList.end()) {
        return vertexList[id];
    }
    
    Vertex* artist = new Vertex(id, artistName);
    vertexList.insert(std::make_pair(id, artist));

    return artist;
}

/**
 * Loops through both artists to ensure that there isn't already an edge between the two artists for the
 * same song. If not, construct an edge and add it to the edge list. Then, add the edge to the list of
 * edges held in each vertex.
 */
bool Graph::insertEdge(Vertex* firstArtist, Vertex* secondArtist, string songID, string songTitle, int songLength) {
    if (checkIfEdgeExists(firstArtist, secondArtist, songID)) {
        return false;
    }

    Edge* song = new Edge(firstArtist->getId(), secondArtist->getId(), songID, songTitle, songLength);
    edgeList.push_back(song);

    firstArtist->addEdge(song);
    secondArtist->addEdge(song);

    return true;
}

bool Graph::checkIfEdgeExists(Vertex* firstArtist, Vertex* secondArtist, string songID) {
    vector<Edge> firstArtistSongs = getIncidentEdges(firstArtist);

    for (Edge song : firstArtistSongs) {
        std::pair<std::string, std::string> songArtists = song.getArtistIDs();
        
        if (song.getId() == songID && ((vertexList[songArtists.first]->getName() == firstArtist->getName() && vertexList[songArtists.second]->getName() == secondArtist->getName()) 
            || (vertexList[songArtists.first]->getName() == secondArtist->getName() && vertexList[songArtists.second]->getName() == firstArtist->getName()))) {
            return true;
        }
    }

    return false;
}

vector<Vertex*> Graph::getAllVertices() {
    vector<Vertex*> artists;

    for (std::pair<string, Vertex*> cur : vertexList) {
        artists.push_back(cur.second);
    }

    return artists;
}

vector<Edge> Graph::getAllEdges() {
    vector<Edge> edges;
    for (Edge* e : edgeList) {
        edges.push_back(*e);
    }
    return edges;
}

vector<Edge> Graph::getIncidentEdges(Vertex* v) {
    vector<Edge> edges;
    for (Edge* e : v->getEdges()) {
        edges.push_back(*e);
    }
    return edges;
}

// CHANGE RETURN TYPE!
void Graph::BFS() {
    BFS(0);
}

// !!! CHANGE RETURN TYPE
void Graph::BFS(unsigned index) {
    vector<Vertex*> artistsVect = getAllVertices(); // stores vertices of all artists
    if (index < vertexList.size()) {

        // vector of vertices
        std::vector<Vertex*> vertices = getAllVertices();

        // struct unordered_set for managing visited vertices
        // struct VertexHash
        // {
        // std::size_t operator()(const Vertex& v) const
        //     {
        //     using std::size_t;
        //     using std::hash;
        //     using std::string;

        //     return hash<string>()(v.getId());
        //     }
        // };
        // std::unordered_set<Vertex, VertexHash> visited;

        // queue for BFS
        list<Vertex*> queue;

        // queue up first vertex
        // visited.insert(*vertices[index]);
        queue.push_back(vertices[index]);

        while (!queue.empty()) {
            // dequeue front most vertex
            Vertex* v = queue.front();
            queue.pop_front();

            // print vertex data
            v->print();

            // get adjacent vertices using edgeList
            std::vector<Edge*> adjList = v->getEdges();
            for (auto it = adjList.begin(); it != adjList.end(); it++) {
                std::pair<string, string> ids = (*it)->getArtistIDs();
                string v1 = ids.first;
                string v2 = ids.second;
                if (v1 == v->getId()) { // v1 is the artist, so try to add v2 to queue
                    // if (!visit["idx"]) {
                    //     queue.push_back("v2"); // O(1) lookup based on ID
                    // }
                } else { // v2 is the artist, so try to add v1 to queue
                    // if (!visit["idx"]) {
                    //     queue.push_back("v1");
                    // }
                }
            }
        }
    }
}
