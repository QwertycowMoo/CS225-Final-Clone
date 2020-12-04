
#include "graph.h"

#include <unordered_map>

Graph::Graph() {

}

void Graph::InsertVertex(Vertex v) {
    vertexList.insert(std::make_pair(v, 0));
}

bool Graph::InsertEdge(Vertex source, Vertex dest, Edge label) {
    Edge* newEdge = new Edge(label);
    

}

void Graph::RemoveVertex(Vertex v) {
    
}




