#include "vertex.h"
#include <iostream>

Vertex::Vertex(const std::string& id, const std::string& name) : id_(id), name_(name) {
    adjacencyList = std::vector<Edge*>();
}

std::string Vertex::getId() const{
    return id_;
}

std::string Vertex::getName() const{
    return name_;
}

void Vertex::setId(std::string id) {
    id_ = id;
}

void Vertex::setName(std::string name) {
    name_ = name;
}

std::vector<Edge*> Vertex::getEdges() const{
    return adjacencyList;
}

void Vertex::addEdge(Edge* song) {
    adjacencyList.push_back(song);
}

void Vertex::print() {
    std::cout << name_ << std::endl;
}

bool Vertex::operator==(const Vertex& other) const {
    if (name_ == other.getName()) {
        if (id_ == other.getId()) {
            if (adjacencyList == other.getEdges()) {
                return true;
            }
        }
    }

    return false;
}
