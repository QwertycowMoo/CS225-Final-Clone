#include "spotify.h"

int main(int argc, char** argv) {
    Spotify spotify;
    spotify.getAccessToken();
    string formattedArtist = Spotify::formatArtistInput("Jacob Collier");
    json jArtistInfo= spotify.makeRequest(formattedArtist);
    spotify.cleanJson(jArtistInfo); //passed by reference so it will make changes to the original JSON object

    std::cout << jArtistInfo.dump(4) << std::endl;


}