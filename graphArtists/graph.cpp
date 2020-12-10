
#include "graph.h"
#include <iostream>

Graph::~Graph() {
    for (unordered_map<string, Vertex*>::iterator it = vertexList.begin(); it != vertexList.end(); ++it) {
        delete it->second;
    }

    for (Edge* e : edgeList) {
        delete e;
    }
}

Vertex* Graph::insertVertex(const string& id, const string& artistName) {
    if (vertexList.find(id) != vertexList.end()) {
        return vertexList[id];
    }
    
    Vertex* artist = new Vertex(id, artistName);
    vertexList.insert(std::make_pair(id, artist));

    return artist;
}

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

Edge* Graph::checkIfEdgeExists(Vertex* firstArtist, Vertex* secondArtist, string songID) {
    for (Edge* song : firstArtist->getEdges()) {
        std::pair<std::string, std::string> songArtists = song->getArtistIDs();
        
        if (song->getId() == songID && ((vertexList[songArtists.first]->getName() == firstArtist->getName() && 
        vertexList[songArtists.second]->getName() == secondArtist->getName()) 
            || (vertexList[songArtists.first]->getName() == secondArtist->getName() 
            && vertexList[songArtists.second]->getName() == firstArtist->getName()))) {
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

list<Vertex*> Graph::BFS(string name) {
    vector<Vertex*> artists = getAllVertices();
    string temp = "";
    for (Vertex* v : artists) {
        if (v->getName() == name) {temp = v->getId(); }
    }
    if (temp.empty()) {
        std::cout << "No artist found.. :(" << std::endl;
        return list<Vertex*>(); 
    }
    auto it = vertexList.find(temp);
    unsigned index = distance(vertexList.begin(), it);
    return BFS(index);
}

list<Vertex*> Graph::BFS(unsigned index) {
    // vector of vertices
    vector<Vertex*> artistsVect = getAllVertices(); // stores vertices of all artists
    if (index >= artistsVect.size()) {return list<Vertex*>(); }
        // keeps count of the total number of vertices
        unsigned vertexCount = 1;

        // visitation bools - initialized unordered map based on artist IDs.
        unordered_map<Vertex*, bool> visited;
        for (Vertex* v : artistsVect) {
            visited.insert(std::pair<Vertex*, bool>(v, false));
        }

        // queue and return queue for BFS
        list<Vertex*> queue;
        list<Vertex*> returnQueue;

        // queue up first vertex
        queue.push_back(artistsVect[index]);
        returnQueue.push_back(artistsVect[index]);
        visited[artistsVect[index]] = true;

        while (!queue.empty()) {
            // dequeue front most vertex
            Vertex* v = queue.front();
            queue.pop_front();

            // get adjacent vertices using edgeList
            std::vector<Edge*> adjList = v->getEdges();
            for (auto it = adjList.begin(); it != adjList.end(); it++) {
                std::pair<string, string> ids = (*it)->getArtistIDs();
                Vertex* v1 = vertexList[ids.first];
                Vertex* v2 = vertexList[ids.second];
                if (!visited.at(v1)) {
                    queue.push_back(v1);
                    returnQueue.push_back(v1);
                    vertexCount++;
                    visited[v1] = true; 
                } 
                if (!visited.at(v2)) {
                    queue.push_back(v2);
                    returnQueue.push_back(v2);
                    vertexCount++; 
                    visited[v2] = true; 
                }
                if (vertexCount == artistsVect.size()) {
                    break;
                }
            }
        }
    return returnQueue;
}