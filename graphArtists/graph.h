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
        bool InsertEdge(Vertex source, Vertex dest, Edge* label);
        Edge RemoveEdge(Vertex source, Vertex dest);

        vector<Vertex> getAllVertices();
        vector<Edge> getAllEdges()
        vector<Edge> getIncidentEdges(Vertex v);


    private:
        unordered_map<Vertex, int> VertexList; // maps key to int index
        list<Edge> edgeList; // linked list of edges
};
