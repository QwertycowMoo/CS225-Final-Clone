#pragma once

#include "edge.h"
#include <string>
#include <list>

class Vertex {
    public:
        Vertex(std::string id, std::string name);

    // *** Helper functions ***
        // getter
        std::string getId();
        std::string getName();

        // setter
        void setId(std::string id);
        void setName(std::string name);
        
        void addEdge(Edge& song);

        std::vector<Edge> getEdges();

    private:
        // the artist's ID (unique Spotify string)
        std::string id_;
        // the artist's name
        std::string name_;

        std::vector<Edge> adjacencyList;
};