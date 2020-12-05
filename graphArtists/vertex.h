#pragma once

#include "edge.h"
#include <string>
#include <vector>

class Vertex {
    public:
        Vertex(const std::string& id, const std::string& name);

    // *** Helper functions ***
        // getter
        std::string getId();
        std::string getName();

        // setter
        void setId(std::string id);
        void setName(std::string name);
        
        void addEdge(Edge* song);

        void print();

        std::vector<Edge*> getEdges();

    private:
        // the artist's ID (unique Spotify string)
        std::string id_;
        // the artist's name
        std::string name_;

        std::vector<Edge*> adjacencyList;
};