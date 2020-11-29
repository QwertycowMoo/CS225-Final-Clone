#include "spotify.h"
#include <sstream>

string Spotify::data = "";

size_t Spotify::writeCallback(char* buf, size_t size, size_t nmemb, void* up) {
    //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer
    for (unsigned long c = 0; c<size*nmemb; c++)
    {
        Spotify::data.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}

const char* Spotify::getEncodedIdSecret() {
     //creating the base64encoding of client id and secret
    std::string client_id_secret = CLIENT_ID + ":" + CLIENT_SECRET;
    std::string encoded_id_secret = base64_encode(client_id_secret);
    std::string auth_header = "Authorization: Basic " + encoded_id_secret;
    const char * char_ptr_auth_header = auth_header.c_str(); //need to convert it into a character pointer
    return char_ptr_auth_header;
}

void Spotify::getAccessToken() {
    curl = curl_easy_init();
    if (curl) {
        //we're going to access the Spotify API by using the Client Credentials Flow
        //https://developer.spotify.com/documentation/general/guides/authorization-guide/#client-credentials-flow
        //first curl the api/token endpoint with the header with a base64 encoded clientkey:clientsecret
        //that will return a json object with a access token
        //Then we can access any public endpoint by adding that access token in the header of the curl
        curl_easy_setopt(curl,  CURLOPT_URL, "https://accounts.spotify.com/api/token");
        
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        //the CURLOPT_WRITEFUNCTION writes things to a buffer, can use this to process the data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Spotify::writeCallback);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //verbose information
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        //Need to set headers - need to know the length of the file before posting.
        //We build our own list of headers and then pass that list to libcurl
        struct curl_slist *headers = NULL;
           
        headers = curl_slist_append(headers, getEncodedIdSecret());
        std::string str_data = "grant_type=client_credentials";
        const char* post_data = str_data.c_str();
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

        //reuse the handle (curl) if making another transfer

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            json j_access_token;
            j_access_token = json::parse(Spotify::data); //we can get the json data from this data
            hasAccessToken = true;
            accessToken = j_access_token["access_token"];
        } else {
            std::cout << "something went wrong! Please try again" << std::endl;
        }
        
    }
}

string Spotify::formatArtistInput(string artist) {
    //go through the command line arguments and take the words and turn it into a query
    string query;
    std::istringstream iss(artist);
    //uses string stream to split the artist with spaces into a vector
    std::vector<string>artistSplit((std::istream_iterator<string>(iss)), std::istream_iterator<string>()); 
    //processes the vector into an encoded form for http requests
    for (size_t i = 0; i < artistSplit.size(); i++) {
        query += artistSplit[i];
        if (i < artistSplit.size() - 1) {
            query += "%20"; //hexsign for the " " space character
        }
    }
    return query;
}

json Spotify::makeRequest(string formattedArtistQuery) {
    //we got the access token now, use it to access a track
    curl_easy_reset(curl);

    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
    //the CURLOPT_WRITEFUNCTION writes things to a buffer, can use this to process the data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Spotify::writeCallback);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //verbose information
    Spotify::data = "";

    //curl is a little piss baby and wont take anything other than char*
    curl_easy_setopt(curl,  CURLOPT_URL, ("https://api.spotify.com/v1/search?q=" + formattedArtistQuery + "&type=album").c_str()); 
    std::string acc_token_header = "Authorization: Bearer " + accessToken;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, acc_token_header.c_str());
    std::cout << "header data: " << headers->data << std::endl;

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    std::cout << "performing curl" << std::endl;
    CURLcode res = curl_easy_perform(curl);

    json j_playlist;
    j_playlist = json::parse(Spotify::data);
    return j_playlist;

    
}

json Spotify::cleanJson(json& rawResponse) {
    json& albums = rawResponse["albums"];

    for (size_t i = 0; i < albums["items"].size(); i++) {
        json& toRemove = albums["items"][i];
        toRemove.erase("available_markets");
        toRemove.erase("release_date");
        toRemove.erase("release_date_precision");
        toRemove.erase("href");
        toRemove.erase("images");
        toRemove.erase("type");
        for (size_t j = 0; j < toRemove["artists"].size(); j++) {
            json& toRemoveArtists = toRemove["artists"][j];
            toRemoveArtists.erase("external_urls");
        }   
        toRemove.erase("external_urls"); //"spotify": "https://open.spotify.com/album/1T097JCsLabSVK0ZCwSOjs"

    }  
    return rawResponse;
    
}
