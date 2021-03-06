#pragma once

#include "edge.h"
#include "vertex.h"

#include <vector>
#include <unordered_map>
#include <map>
#include <list>
#include <string>
#include <unordered_set>

using std::list;
using std::unordered_map;
using std::map;
using std::vector;
using std::string;

/**
 * A weighted, undirected graph implementation using an adjacency list.
 * Intended to hold artists as verticies and songs as edges. Weights are song durations.
 */
class Graph {
    public:
        /**
         * Default constructor
         */
        Graph();
        ~Graph();

        /**
         * inserts a vertex into our hashmap if it doesn't exist
         * @param artistName name of the artist
         * @param id artist's Spotify ID
         * @return the pointer to the vertex added, or a pointer to the vertex with the exisitng id
         * */
        Vertex* insertVertex(const string& artistName, const string& id);

        /**
         * inserts an Edge into our edgelist and updates the vertices' adjacency lists
         * Since our edge class cannot hold Vertices as it would be circular header files, we implement the pointers back by storing the artist IDs
         * @param firstArtist source artist
         * @param firstArtist destination artist
         * @param songTitle stored in edge class, title of song
         * @param songID stored in edge class, song's Spotify ID
         * @param songLength stored in edge class, length of song in ms
         * @return whether this was a repeat edge or not
         * */
        bool insertEdge(Vertex* firstArtist, Vertex* secondArtist, string songTitle, string songID, int songLength);

        /**
         * gets all vertices in our graph
         * @return vector of pointers of all our vertices
         * */
        vector<Vertex*> getAllVertices() const;

        /**
         * gets all edges in our graph
         * @return vector of all edges in our graph
         * */
        vector<Edge> getAllEdges();

        /**
         * gets all the incident edges of a vertex
         * @param v pointer to the vertex that we want the incident edges of
         * @return vector of all the edges that come from this vertex
         * */
        vector<Edge> getIncidentEdges(Vertex* v) const;
        
        /**
         * checks whether the edge exists, in O(deg(v)).
         * Since the graph is undirected, it the order of the artists does not matter
         * @param firstArtist vertex pointer to the source artist
         * @param secondArtist vertex point to the destination artist
         * @param songID song's Spotify ID
         * @return whether or not the edge exists in our graph
         * */
        Edge* checkIfEdgeExists(Vertex* firstArtist, Vertex* secondArtist, string songID);

        /**@TODO, test for functionality
         * gives a vertex given the id, basically a search
         * */
        Vertex* findVertex(string id);
        
        Vertex* findVertexFromName(string name);

        string findNameFromID(string id);


        /**
         * performs a call to BFS(int index) with the index defaulted to the position of the artist's name in the VertexList
         * this will likely be called since the traversal is based on the starting vertex
         * @param name the name of the artist to begin the traversal at
         */ 
        list<Vertex*> BFS(string name);

        /**
         * performs a breadth-first search of the graph object
         * @param index index of the vertex to start the traversal from
         */
        list<Vertex*> BFS(unsigned index);

    private:
        unordered_map<string, Vertex*> vertexList; // maps artist id to vertex
        vector<Edge*> edgeList; // linked list of edges
        unordered_map<string, string> nameToIdMap;
};
