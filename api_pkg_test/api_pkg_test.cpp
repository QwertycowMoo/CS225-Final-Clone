#include <curl/curl.h>
#include <string>
#include <iostream>
#include "single_include/nlohmann/json.hpp"
#include "keys.h"
using json = nlohmann::json;
using std::string;


//to compile: clang++ api_pkg_test.cpp -std=c++11 -l curl
string data;
size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up) {
    //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}

//access key: jg3OTQwNGYzNzViNGNhMDkyZGJmMDI2Yjg1YzhkN2Q6ZGQ4Njk4MjExYzQyNDhhNTgzOTMyM2ZiNzExNWNmNzkgDQo=
//spotify:playlist:7DYJeAV6l6GwfXLQtLV5Rd

int main(int argc, char** argv) {
    CURL *curl = curl_easy_init();
    if (curl) {

        //we're going to access the Spotify API by using the Client Credentials Flow
        //https://developer.spotify.com/documentation/general/guides/authorization-guide/#client-credentials-flow
        //first curl the api/token endpoint with the header with a base64 encoded clientkey:clientsecret
        //that will return a json object with a access token
        //Then we can access any public endpoint by adding that access token in the header of the curl
        curl_easy_setopt(curl,  CURLOPT_URL, "https://api.spotify.com/v1/playlists/spotify:playlist:7DYJeAV6l6GwfXLQtLV5Rd");
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        curl_easy_perform(curl);

        std::cout << std::endl << data << std::endl;


        curl_easy_cleanup(curl);
        curl_global_cleanup();

        return 0;
    }
}

