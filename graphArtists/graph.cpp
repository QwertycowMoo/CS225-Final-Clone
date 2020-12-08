
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

//O(deg(v))
Edge* Graph::checkIfEdgeExists(Vertex* firstArtist, Vertex* secondArtist, string songID){
    //vector<Edge> firstArtistSongs = getIncidentEdges(firstArtist);

    for (Edge* song : firstArtist->getEdges()) {
        std::pair<std::string, std::string> songArtists = song->getArtistIDs();
        
        if (song->getId() == songID && ((vertexList[songArtists.first]->getName() == firstArtist->getName() && vertexList[songArtists.second]->getName() == secondArtist->getName()) 
            || (vertexList[songArtists.first]->getName() == secondArtist->getName() && vertexList[songArtists.second]->getName() == firstArtist->getName()))) {
            return song;
        }
    }

    return nullptr;
}

vector<Vertex*> Graph::getAllVertices() const{
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

vector<Edge> Graph::getIncidentEdges(Vertex* v) const {
    vector<Edge> edges;
    for (Edge* e : v->getEdges()) {
        edges.push_back(*e);
    }
    return edges;
}

Vertex* Graph::findVertex(string id) {
    //if vertex exists since this would create a new vertex in the hashmap i think
    if (vertexList.find(id) == vertexList.end()) {
        std::cout << "This vertex does not exist, sorry" << std::endl;
        return nullptr;
    }
    return (vertexList.find(id))->second;
}


