#include <curl/curl.h>
#include <string>
#include <iostream>

using std::string;

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

int main(int argc, char** argv) {
    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl,  CURLOPT_URL, "https://github-dev.cs.illinois.edu/cs225-fa20/erf3-caleqw2-kjzhou2-evanmm3");
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

