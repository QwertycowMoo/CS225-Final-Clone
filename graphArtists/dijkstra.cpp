#import "dijkstra.h"
#import <map>
#import <unordered_map>
#import <priority_queue>
#import <vector>
#import <unordered_set>

using std::map;
using std::priority_queue;
using std::unordered_map;
using std::unordered_set;

Graph Dijkstra::performDijkstra(Graph* g, Vertex* source){


    for (Vertex* v : g.getAllVertices()) {
        distances[*v] = INT_MAX;
        pred[*v] = nullptr;
    }

    //sets up the beginning
    unordered_set<Vertex> visited;
    distances[*source] = 0;
    
    //graph that will result in the full dijkstra SSSP tree
    Graph result;

    for (Vertex* v : g.getAllVertices()) {
        //get smallest path length vertex
        //we're using a map which is sorted, so we can do this in O(logn)
        Vertex min = distances[0].first;
        
        size_t i = 0;
        //find a vertex that we have not visited yet
        while (visited.find(min) != visited.end()) {
            i++;
            min = distances[i].first;
        }
        
        
        


        //add vertex to the dijk graph
        result.addVertex(min.getId(), min.getName());

        //since we dereferenced a pointer to a Vertex, the map Vertex objects should have its adjacency list as well
        vector<Edge*> adj = min.getEdges(); 
        for (Edge* e : adj) {
            Vertex* toUpdate = g.findVertex(e->getArtistIDs().second);

            //find length of path preceeding this edge
            int precPathLen = distances[min];

            if (e->getLength() + precPathLen < distances[toUpdate]) {
                //update
                distances[toUpdate] = e->getLength() + precPathLen;
                //doing this instead of just min because min will be deleted while the graph will stay
                pred[toUpdate] = result.findVertex(min.getId());
            }
        }
        
        //we visited this node, add to visited set
        visited.add(min); 
    }

    //build the graph by recursing through the predecessor keys


    
}

vector<Edge> Dijkstra::shortestPath(Graph g, Vertex source, Vertex dest);