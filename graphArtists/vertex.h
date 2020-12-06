#pragma once

#include "edge.h"
#include <string>
#include <vector>

/**
 * Class representing an Artist in the graph;
 * Each Artist has connections to other Artists based on collaborations on songs (Edges)
 */
class Vertex {
    public:
        Vertex(const std::string& id, const std::string& name);

        // getter
        std::string getId();
        std::string getName();

        // setter
        void setId(std::string id);
        void setName(std::string name);
        
        /**
         * adds an edge to this vertex's adjacency list
         * @param song edge to be added
         * */
        void addEdge(Edge* song);

        /**
         * prints a string representation of the vertex object
         * */
        void print();

        /**
         * gets all the edges in the adjacency list of this vertex
         * @return vector of all adjacent edges
         * */
        std::vector<Edge*> getEdges();

    private:
        // the artist's ID (unique Spotify string)
        std::string id_;
        // the artist's name
        std::string name_;
        // list of edges which contain the artist as a vertex.
        std::vector<Edge*> adjacencyList;
};
