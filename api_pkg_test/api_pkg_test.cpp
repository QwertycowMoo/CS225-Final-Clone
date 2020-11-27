#include <curl/curl.h>
#include <string>
#include <iostream>
#include "single_include/nlohmann/json.hpp"
#include "keys.h" //in .gitignore
#include "base64.h"
using json = nlohmann::json;
using std::string;
using std::cout;
using std::endl;

//to compile: clang++ api_pkg_test.cpp -std=c++11 -l curl
string data;
size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up) {
    //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer
    for (unsigned long c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}

//access key: jg3OTQwNGYzNzViNGNhMDkyZGJmMDI2Yjg1YzhkN2Q6ZGQ4Njk4MjExYzQyNDhhNTgzOTMyM2ZiNzExNWNmNzkgDQo=
//spotify:playlist:7DYJeAV6l6GwfXLQtLV5Rd



int main(int argc, char** argv) {
    json j;
    j["instrument"] = "guitar";
    std::vector<int> v = {1,2,3,4,5};
    j["numbers"] = v;
    cout << j << endl;
    cout << endl << endl;
    CURL *curl = curl_easy_init();
    if (curl) {
        std::cout << CLIENT_ID << std::endl;
        std::cout << CLIENT_SECRET << std::endl;
        //we're going to access the Spotify API by using the Client Credentials Flow
        //https://developer.spotify.com/documentation/general/guides/authorization-guide/#client-credentials-flow
        //first curl the api/token endpoint with the header with a base64 encoded clientkey:clientsecret
        //that will return a json object with a access token
        //Then we can access any public endpoint by adding that access token in the header of the curl
        curl_easy_setopt(curl,  CURLOPT_URL, "https://accounts.spotify.com/api/token");
        
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        std::string response_string;
        std::string header_string;
        //the CURLOPT_WRITEFUNCTION writes things to a buffer, can use this to process the data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        //Need to set headers - need to know the length of the file before posting.
        //We build our own list of headers and then pass that list to libcurl
        struct curl_slist *headers = NULL;
            //creating the base64encoding of client id and secret
            std::string client_id_secret = CLIENT_ID + ":" + CLIENT_SECRET;
            std::string encoded_id_secret = base64_encode(client_id_secret);
            std::cout << client_id_secret << std::endl;
            std::cout << encoded_id_secret << std::endl;
            std::string auth_header = "Authorization: Basic " + encoded_id_secret;
            const char * char_ptr_auth_header = auth_header.c_str(); //need to convert it into a character pointer
            std::cout << char_ptr_auth_header << std::endl;
        headers = curl_slist_append(headers, char_ptr_auth_header);
        std::string str_data = "grant_type=client_credentials";
        const char* post_data = str_data.c_str();
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        
        //curl_slist_free_all(headers); // free header list
        std::unique_ptr<std::string> httpData(new std::string());
        //reuse the handle (curl) if making another transfer

        //So it seems that the curl only works with the specific -X "POST" specification and not with just the -d. MAybe try to specifically type the request?
        CURLcode res = curl_easy_perform(curl);
        json j_access_token;
        j_access_token = json::parse(data); //we can get the json data from this data
        string acc_token = j_access_token["access_token"];

        cout << endl << endl << acc_token << endl;
        if (res == CURLE_OK) {
            //we got the access token now, use it to access a track
           curl_easy_reset(curl);

            curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
            curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
            //the CURLOPT_WRITEFUNCTION writes things to a buffer, can use this to process the data
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
            data = "";
            curl_easy_setopt(curl,  CURLOPT_URL, "https://api.spotify.com/v1/playlists/7DYJeAV6l6GwfXLQtLV5Rd");
            std::string acc_token_header = "Authorization: Bearer " + acc_token;
            curl_slist_free_all(headers);
            headers = NULL;
            headers = curl_slist_append(headers, acc_token_header.c_str());
            cout << "header data: " << headers->data << endl;

            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            cout << "performing curl" << endl;
            res = curl_easy_perform(curl);
            json j_playlist;
            //j_playlist = json::parse(data);
            cout << data << endl;
        }
        
        curl_easy_cleanup(curl);
        curl_global_cleanup();



        /*******************************************
         * 
         * SPOTIFY FLOW
         * 
         * *****************************************/
        //First request authorization
        //Make a POST request to https://accounts.spotify.com/api/token
        //Data for POST request is "grant_type=client_credentials"
        //Get the Client ID and Secret
        //Create a header with the format "Authorization: Basic <base64Encoded client_id:client_secret>"
        //Make this POST request
        //Callback will return a JSON object with an access token
        //Parse the JSON to get the access token for actually accessing the API

        //Second use access token to access Spotify API
        //Make a GET request at https://api.spotify.com/v1/......
        //Create a header with the format "Authorization: Bearer <access_token>"
        //Parse the JSON to create a graph using this data
        return 0;
    }
}

