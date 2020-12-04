#include "edge.h"
#include "vertex.h"
#include <unordered_map>
#include <list>
#pragma once

using std::list;
using std::unordered_map;

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

        void InsertVertex(Vertex v);
        void RemoveVertex(Vertex v);
        bool InsertEdge(Vertex source, Vertex dest, Edge label);
        Edge RemoveEdge(Vertex source, Vertex dest);

    private:
        unordered_map<Vertex, int> vertexList; // maps key to int index
        list<Edge> edgeList; // linked list of edges

        // create the new edge object
        // insert into the edge list in the graph
        // go to each of the verticies of that edge and add that edge to its adjacency list
        // in that edge, have a list of pointers that point back to the adjacency list
};
