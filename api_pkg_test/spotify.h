#include <curl/curl.h>
#include <string>
#include <iostream>
#include "single_include/nlohmann/json.hpp"
#include "keys.h" //in .gitignore
#include "base64.h"
using json = nlohmann::json;
using std::string;

#pragma once

class Spotify {
    public:
    /**
     * @params all supplied by curl, 
     * @return amount of bytes handled by the callback function
     * Callback Function for the Spotify API to write data to
     * */
    static size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);
    /**
     * Gets the access token from the accounts.spotify.com/api/token to use in the actual requests
     * */
    void getAccessToken();
    
    /**
     * Formats the artist from either cin or some other input into encoded spaces for http transfer
     * */
    static string formatArtistInput(string artist);
    /**
     * Makes the request give this specific artist, needs support for specific Artist ids, maybe overload?
     * @return a json object with all information of the first twenty albums from this artists - may need to change since there could be multiple artists given the string
     * */
    json makeRequest(string formattedArtist);

    /**
     * Cleans the response json so that its only the information that we need. 
     * */
    json cleanJson(json& rawResponse);

    private:
    /**
     * Gets the client id and secret and transforms them into the base64 encoded for http transfer
     * */
    const char* getEncodedIdSecret();

    CURL* curl;
    static string data;
    bool hasAccessToken;
    string accessToken;
};

