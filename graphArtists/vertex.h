#pragma once

#include <string>
#include <list>

using std::string;

class Vertex {
    public:
        Vertex(const string& id, const string& name);

    // *** Helper functions ***
        // getter
        string getId();
        string getName();

        // setter
        void setId(string id);
        void setName(string name);
        
        void addEdge(Edge& song);

        std::vector<Edge> getEdges();

    private:
        // the artist's ID (unique Spotify string)
        string id_;
        // the artist's name
        string name_;

        std::vector<Edge> adjacencyList;
};
