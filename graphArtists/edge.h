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

        // getters
        string getId();
        string getName();
        int getLength();

        // setters
        void setId(string id);
        void setName(string name);
        void setLength(int length_ms);

        /**
         * prints a string representation of the edge object
         * */
        void print();

        /**
         * converts milliseconds to a string representation of minutes and seconds
         * */
        string msToMinSecs(int ms);

        /**
         * @return the source and destination artists for this edge
         * */
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