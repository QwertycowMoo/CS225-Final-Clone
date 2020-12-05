#pragma once

#include <string>
#include <list>
#include <vector>

using std::string;
using std::pair;

/**
 * Class representing a Song in the graph;
 * Each edge requires two connecting vertices, (two artists who work on the given song)
 */
class Edge {
    public:
        Edge(const string& artistID1, const string& artistID2, const string& id, const string& name, int length_ms);

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
        pair<string, string> getArtistIDs();
    private:
        // The 2 artists listed on the song
        pair<string, string> artistIDs;
        // The song ID, (unique Spotify string)
        string id_;
        // The song name, (common title)
        string name_;
        // The length of the song, (milliseconds)
        int length_ms_;
};