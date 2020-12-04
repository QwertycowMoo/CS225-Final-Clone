#pragma once

#import "graph.h"
#import <queue>
#import <vector>

class Dijkstra {
    public:
    Graph performDijkstra(Graph g, Vertex source);
    vector<Edge> shortestPath(Graph g, Vertex source, Vertex dest);

    private:
        dijk_graph_;
}