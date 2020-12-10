#include "landmark.h"

vector<Edge*> LandmarkPath::landmarkPath(Graph& g, Vertex* artist1, Vertex* landmarkArtist, Vertex* artist3){
    vector<Edge*> result;
    Dijkstra d;
    vector<Edge*> artist1_to_landmark = d.shortestPath(g, artist1, landmarkArtist);
    result = artist1_to_landmark;
    vector<Edge*> landmark_to_artist3 = d.shortestPath(g, landmarkArtist, artist3);
    result.insert(result.end(), landmark_to_artist3.begin(), landmark_to_artist3.end());
    return result;
}