#include "vertex.h"

/**
 * Constructor for Vertex class
 */ 
Vertex::Vertex(const string& id, const string& name):id_(id), name_(name){
    adjacencyList = std::list<Edge>();
};

/**
 * @return the artist's ID
 */ 
string Vertex::getId() {
    return id_;
}

/**
 * @return the artist's name
 */ 
string Vertex::getName() {
    return name_;
}

/**
 * Sets the ID of a given artist's vertex
 * @param id artist ID to set
 */ 
void Vertex::setId(string id) {
    id_ = id;
}

/**
 * Sets the name of a given artist's vertex
 * @param name artist name to set
 */ 
void Vertex::setName(string name) {
    name_ = name;
}

std::vector<Edge> Vertex::getEdges() {
    return adjacencyList;
}

void Vertex::addEdge(Edge& song) {
    adjacencyList.push_back(song);
}