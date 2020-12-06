#pragma once

#include "graph.h"
#include <unordered_map>

using std::unordered_map;

class Dijkstra {
    public:
    
    ~Dijkstra();
    /**
     * finds the shortestPath given the source and destination using dijkstra's algorithm
     * @param source start vertex
     * @param dest end vertex
     * */
    vector<Edge*> shortestPath(Graph& g, Vertex* source, Vertex* dest);

    private:

        //Object to keep the previous vertex as well as the songId so that we can find song name later
        struct predObj {
            string songId;
            Vertex* prev;
            predObj(string song, Vertex* vertex) {
                songId = song;
                prev = vertex;
            }
        };

        //Priority Queue object for accessing the lowest cost path so far
        struct pqObj {
            int length;
            Vertex* vertex;
            pqObj(Vertex* v, int l) {
                length = l;
                vertex = v;
            }
            bool operator<(const pqObj other) const {
                return length < other.length;
            }
        };

        struct VertexHash
        {
            std::size_t operator()(const Vertex& v) const
            {
                using std::size_t;
                using std::hash;
                using std::string;

                return hash<string>()(v.getId());
            }
        };

        //these two are kept here so that shortest path can just build the path without having to create a graph
        unordered_map<Vertex, int, VertexHash> distances;
        unordered_map<Vertex, predObj*, VertexHash> pred;

        
        /**
        * performs Dijkstra's algorithm on the graph with the source vertex
        * @param g graph
        * @param source source vertex
        * */
        void performDijkstra(Graph& g, Vertex* source);
};