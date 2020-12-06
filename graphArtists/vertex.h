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
        std::string getId() const;
        std::string getName() const;

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

        /**@TODO 
         * = constructor and copy constructor
         * */

    private:
        // the artist's ID (unique Spotify string)
        std::string id_;
        // the artist's name
        std::string name_;

        std::vector<Edge*> adjacencyList;
};