#include "vertex.h"

/**
 * Constructor for Vertex class
 */ 
Vertex::Vertex(const std::string& id, const std::string& name):id_(id), name_(name){
    adjacencyList = std::vector<Edge>();
};

/**
 * @return the artist's ID
 */ 
std::string Vertex::getId() {
    return id_;
}

/**
 * @return the artist's name
 */ 
std::string Vertex::getName() {
    return name_;
}

/**
 * Sets the ID of a given artist's vertex
 * @param id artist ID to set
 */ 
void Vertex::setId(const std::string& id) {
    id_ = id;
}

/**
 * Sets the name of a given artist's vertex
 * @param name artist name to set
 */ 
void Vertex::setName(const std::string& name) {
    name_ = name;
}

std::vector<Edge> Vertex::getEdges() {
    return adjacencyList;
}

void Vertex::addEdge(Edge& song) {
    adjacencyList.push_back(song);
}