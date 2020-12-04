
#pragma once

#include <string>
#include <list>

using std::string;
 
/**
 * Class representing a Song in the graph;
 * Each edge requires two connecting vertices, (two artists who work on the given song)
 */
class Edge {
    public:
        Edge(string id, string name, int length_ms);
        Edge(string id, string name);

    // *** Helper functions ***
        // getter
        string getId();
        string getName();
        int getLength();

        // setter
        void setId(string id);
        void setName(string name);
        void setLength(int length_ms);

        void print();
        string msToMinSecs(int ms);
    private:
        // The song ID, (unique Spotify string)
        string id_;
        // The song name, (common title)
        string name_;
        // The length of the song, (milliseconds)
        int length_ms_;

        std::list<Edge*>* adjacencyList;
};
