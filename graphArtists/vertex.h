#pragma once

#include <string>
#include <list>

using std::string;

class Vertex {
    public:
        Vertex(string id, string name);

    // *** Helper functions ***
        // getter
        string getId();
        string getName();

        // setter
        void setId(string id);
        void setName(string name);

    private:
        // the artist's ID (unique Spotify string)
        string id_;
        // the artist's name
        string name_;

        std::list<Edge*>* adjacencyList;
};
