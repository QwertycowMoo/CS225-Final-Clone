#pragma once

#include "graph.h"


class Dijkstra {
    public:
    
    ~Dijkstra();
    /**
     * finds the shortestPath given the source and destination using dijkstra's algorithm
     * @param source start vertex
     * @param dest end vertex
     * */
    vector<Edge*> shortestPath(const Graph& g, const Vertex& source, const Vertex& dest);

    private:


        struct predObj {
            string songId;
            Vertex* prev;
            predObj(string song, Vertex* vertex) {
                songId = song;
                prev = vertex;
            }
        };
        //these two are kept here so that shortest path can just build the path without having to create a graph
        map<Vertex, int> distances;
        unordered_map<Vertex, predObj*> pred;

        
        /**
        * performs Dijkstra's algorithm on the graph with the source vertex
        * @param g graph
        * @param source source vertex
        * */
        void performDijkstra(Graph& g, Vertex* source);
};