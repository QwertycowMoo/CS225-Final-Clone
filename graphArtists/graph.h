#pragma once

#include "edge.h"
#include "vertex.h"

#include <vector>
#include <unordered_map>
#include <map>
#include <list>
#include <string>

using std::list;
using std::unordered_map;
using std::map;
using std::vector;
using std::string;

/**
 * A weighted, undirected graph implementation using an adjacency list.
 * Intended to hold artists as verticies and songs as edges. Weights are song durations.
 */
class Graph {
    public:
        /**
         * Defualt constructor
         */
        Graph();

        Vertex* insertVertex(const string& artistName, const string& id);
        bool insertEdge(Vertex* firstArtist, Vertex* secondArtist, string songTitle, string songID, int songLength);

        vector<Vertex> getAllVertices();
        list<Edge> getAllEdges();
        vector<Edge> getIncidentEdges(Vertex* v);
        bool checkIfEdgeExists(Vertex* firstArtist, Vertex* secondArtist, string songID);
    private:
        map<string, Vertex*> vertexList; // maps artist id to vertex
        list<Edge> edgeList; // linked list of edges
};
