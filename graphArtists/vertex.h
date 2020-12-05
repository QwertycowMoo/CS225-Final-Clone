#pragma once

#include "edge.h"
#include <string>
#include <list>

class Vertex {
    public:
        Vertex(const std::string& id, const std::string& name);

    // *** Helper functions ***
        // getter
        std::string getId();
        std::string getName();

        // setter
        void setId(const std::string& id);
        void setName(const std::string& name);
        
        void addEdge(Edge& song);

        void print();

        std::vector<Edge> getEdges();

    private:
        // the artist's ID (unique Spotify string)
        std::string id_;
        // the artist's name
        std::string name_;

        std::vector<Edge> adjacencyList;
};