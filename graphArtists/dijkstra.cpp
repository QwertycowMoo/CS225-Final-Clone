#include "dijkstra.h"
#include <unordered_map>
#include <queue>
#include <vector>
#include <unordered_set>
#include <climits>
#include <algorithm>
#include <iostream>

using std::priority_queue;
using std::unordered_set;

Dijkstra::~Dijkstra() {
    //deletes all the predecessor Objects in the predecessor map
    for(pair<const Vertex, predObj*> p : pred) {
        if (p.second) {
            delete p.second;
        }
    }
}

void Dijkstra::performDijkstra(Graph& g, Vertex* source){

    for (Vertex* v : g.getAllVertices()) {
        distances[*v] = INT_MAX;
        pred[*v] = nullptr;
    }

    //sets up the beginning
   
    unordered_set<Vertex, VertexHash> visited;
    distances[*source] = 0;

    //priority queue to find the lowest path length
    priority_queue<pqObj> queue;
    queue.push(pqObj(source, 0));
    //graph that will result in the full dijkstra SSSP tree


    std::cout << "Dijkstra setup done" << std::endl;
    for (Vertex* v : g.getAllVertices()) {
        //get smallest path length vertex
        //we're using a map which is sorted, so we can do this in less time because we're just gonna take the first item not visited
        pqObj queueObject = queue.top();
        queue.pop();
        Vertex* min_ptr = queueObject.vertex;
        Vertex min = *min_ptr;
        // std::cout << "----------------" << std::endl;
        // min.print();
        // std::cout << queueObject.length <<std::endl;
        // std::cout << "----------------" << std::endl;
        //find a vertex that we have not visited yet
        while (visited.find(min) != visited.end()) {
            if (queue.empty()) {
                break;
            }
            queueObject = queue.top();
            queue.pop();
            min_ptr = queueObject.vertex;
            min = *min_ptr;
            // min.print();
        }

        // std::cout << "processing vertex:";
        // min.print();

        //since we dereferenced a pointer to a Vertex, the map Vertex objects should have its adjacency list as well
        vector<Edge*> adj = min.getEdges(); 

        std::cout << "going through the adj edges of size " << adj.size() << ":" << std::endl;
        min.print();
        for (Edge* e : adj) {
            // e->print();
            //std::cout << e->getLength() << std::endl;
            Vertex* toUpdate;

            if (g.findVertex(e->getArtistIDs().second) == min_ptr) {
                toUpdate = g.findVertex(e->getArtistIDs().first);
            } else {
                toUpdate = g.findVertex(e->getArtistIDs().second);
            }
           

            //find length of path preceeding this edge
            int precPathLen = distances[min];

            if (e->getLength() + precPathLen < distances[*toUpdate]) {
                //update
                distances[*toUpdate] = e->getLength() + precPathLen;
                //doing this instead of just min because min will be deleted while the graph will stay
                //std::cout << g.findVertex(min.getId())->getName() << std::endl;
                predObj* p = new predObj(e->getId(), g.findVertex(min.getId()));
                pred[*toUpdate] = p;
            }

            //then add the updated vertex to the queue to be processed
            if (visited.find(*toUpdate) == visited.end()) {
                // std::cout << "adding to the queue: ";
                //  toUpdate->print();
                queue.push(pqObj(toUpdate, distances[*toUpdate]));
            }
            
        }
        //we visited this node, add to visited set
        visited.insert(min); 
    }
    
}

//build the graph by going back through the predecessor keys
vector<Edge*> Dijkstra::shortestPath(Graph& g, Vertex* source, Vertex* dest) {
    //make a check to see if the source or destination actually exists or since its a pointer it should already exist no?
    performDijkstra(g, source);

    std::cout << "finding shortest path" << std::endl;
    //segfault happens here somewhere, i need to fix the edge weight weirdness first
    vector<Edge*> path;
    Vertex* v = dest;
    while(pred[*v]) {
        Vertex* pre = pred[*v]->prev;
        // v->print();
        // pre->print();
        
        Edge* e = g.checkIfEdgeExists(pre, v, pred[*v]->songId); //change checkIfEdgeExists to an Edge pointer
        // e->print();
        path.push_back(e);
        v = pred[*v]->prev;
    }
    std::reverse(path.begin(), path.end());
    return path;
}