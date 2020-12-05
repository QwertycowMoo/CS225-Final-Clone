
#include "graph.h"

#include <unordered_map>

Graph::Graph() {

}

/**
 * Checks the vertex list for vertexes with the current artist. If so, returns a reference to that vertex.
 * Otherwise, it will create a new vertex and add it to the vertex list.
 */
Vertex& Graph::insertVertex(const string& artistName, const string& id) {
    if (vertexList.find(artistName) != vertexList.end()) {
        return vertexList[artistName];
    }

    Vertex artist(id, artistName);
    vertexList.insert(std::make_pair(artistName, artist));
}

/**
 * Loops through both artists to ensure that there isn't already an edge between the two artists for the
 * same song. If not, construct an edge and add it to the edge list. Then, add the edge to the list of
 * edges held in each vertex.
 */
bool Graph::insertEdge(Vertex& firstArtist, Vertex& secondArtist, string songTitle, string songID, int songLength) {
    if (checkIfEdgeExists(firstArtist, secondArtist, songID)) {
        return false;
    }

    Edge song(firstArtist, secondArtist, songTitle, songID, songLength);
    edgeList.push_back(song);

    firstArtist.addEdge(song);
    secondArtist.addEdge(song);

    return true;
}

bool Graph::checkIfEdgeExists(Vertex& firstArtist, Vertex& secondArtist, string songID) {
    vector<Edge> firstArtistSongs = getIncidentEdges(firstArtist);

    for (Edge song : firstArtistSongs) {
        std::pair<Vertex, Vertex> songArtists = song.getArtists();
        if (song.getId() == songID && ((songArtists.first.getName() == firstArtist.getName() && songArtists.second.getName() == secondArtist.getName()) 
            || (songArtists.first.getName() == secondArtist.getName() && songArtists.second.getName() == firstArtist.getName()))) {
            return true;
        }
    }

    return false;
}

vector<Vertex> Graph::getAllVertices() {
    vector<Vertex> artists;

    for (std::pair<string, Vertex> cur : vertexList) {
        artists.push_back(cur.second);
    }

    return artists;
}

list<Edge> Graph::getAllEdges() {
    return edgeList;
}

vector<Edge> Graph::getIncidentEdges(Vertex& v) {
    return v.getEdges();
}



