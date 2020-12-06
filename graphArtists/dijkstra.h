#pragma once

#import "graph.h"


class Dijkstra {
    public:
    /**
     * performs Dijkstra's algorithm on the graph with the source vertex
     * @param g graph
     * @param source source vertex
     * */
    void performDijkstra(Graph g, Vertex source);

    /**
     * finds the shortestPath given the source and destination using dijkstra's algorithm
     * */
    vector<Edge> shortestPath(Graph g, Vertex source, Vertex dest);

    private:
        dijk_graph_;

        //these two are kept here so that shortest path can just build the path without having to create a graph
        map<Vertex, int> distances;
        unordered_map<Vertex, Vertex*> pred;
}