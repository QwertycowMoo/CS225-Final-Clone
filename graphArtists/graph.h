
#pragma once

#include "edge.h"
#include "vertex.h"
#include <unordered_map>
#include <list>
#include <queue>

using std::list;
using std::unordered_map;
using std::queue;

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

        // BFS/Landmark material
        void BFS(Vertex v);
        void landMark();

    private:
        unordered_map<Vertex, int> VertexList; // maps key to int index
        list<Edge> edgeList; // linked list of edges

        // BFS/Landmark material
        Edge getEdge(Vertex v); 
        queue<Vertex> bfsQueue;
        unordered_map<Vertex, bool> bfsVisit;
};
