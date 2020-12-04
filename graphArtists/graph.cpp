
#include "graph.h"

#include <unordered_map>

Graph::Graph() {

}

void Graph::InsertVertex(Vertex v) {
    adjacencyList.insert(std::make_pair(v, list<Edge*>()));
}

void Graph::RemoveVertex(Vertex v) {
    adjacencyList.erase(v);
}




