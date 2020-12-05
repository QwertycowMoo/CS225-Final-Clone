#pragma once
#include "edge.h"
#include "vertex.h"
#include <vector>
#include <unordered_map>
#include <list>

using std::list;
using std::unordered_map;
using std::vector;

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

        Vertex& insertVertex(const string& artistName, const string& id);
        bool insertEdge(Vertex& firstArtist, Vertex& secondArtist, string songTitle, string songID, int songLength);

        vector<Vertex> getAllVertices();
        list<Edge> getAllEdges();
        vector<Edge> getIncidentEdges(Vertex& v);
        bool checkIfEdgeExists(Vertex& firstArtist, Vertex& secondArtist, string songID);

    private:
        unordered_map<string, Vertex> vertexList; // maps key to vertex
        list<Edge> edgeList; // linked list of edges

        // create the new edge object
        // insert into the edge list in the graph
        // go to each of the verticies of that edge and add that edge to its adjacency list
        // in that edge, have a list of pointers that point back to the adjacency list
};
