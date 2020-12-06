#include "dijkstra.h"
#include <map>
#include <unordered_map>
#include <queue>
#include <vector>
#include <unordered_set>
#include <climits>

using std::map;
using std::priority_queue;
using std::unordered_map;
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
    //either use regular set or make a hash function for artists
    struct VertexHash
    {
        std::size_t operator()(const Vertex& v) const
        {
            using std::size_t;
            using std::hash;
            using std::string;

            return hash<string>()(v.getId());
        }
    };
    unordered_set<Vertex, VertexHash> visited;
    distances[*source] = 0;
    
    //graph that will result in the full dijkstra SSSP tree
    Graph result;

    for (Vertex* v : g.getAllVertices()) {
        //get smallest path length vertex
        //we're using a map which is sorted, so we can do this in less time because we're just gonna take the first item not visited
        auto distanceIt = distances.begin();
        Vertex min = distanceIt->first;
        
        size_t i = 0;
        //find a vertex that we have not visited yet
        while (visited.find(min) != visited.end()) {
            distanceIt++;
            min = distanceIt->first;
        }
        
        //add vertex to the dijk graph
        result.insertVertex(min.getName(), min.getId());

        //since we dereferenced a pointer to a Vertex, the map Vertex objects should have its adjacency list as well
        vector<Edge*> adj = min.getEdges(); 
        for (Edge* e : adj) {
            Vertex* toUpdate = g.findVertex(e->getArtistIDs().second);

            //find length of path preceeding this edge
            int precPathLen = distances[min];

            if (e->getLength() + precPathLen < distances[*toUpdate]) {
                //update
                distances[*toUpdate] = e->getLength() + precPathLen;
                //doing this instead of just min because min will be deleted while the graph will stay
                predObj* p = new predObj(e->getId(), result.findVertex(min.getId()));
                pred[*toUpdate] = p;
            }
        }
        
        //we visited this node, add to visited set
        visited.insert(min); 
    }
    
}

//build the graph by going back through the predecessor keys
vector<Edge*> Dijkstra::shortestPath(const Graph& g, const Vertex& source, const Vertex& dest) {
    performDijkstra(g, source);
    vector<Edge*> path;
    Vertex v = dest;
    while(pred[v]) {
        Vertex pre = pred[v]->prev;
        Edge* e = g.checkIfEdgeExists(pre, v, pred[v]->songId); //change checkIfEdgeExists to an Edge pointer
        path.push_back(e);
        v = pred[v]->prev;
    }
    std::reverse(path.begin(), path.end());
}