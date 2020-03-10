#include "datafetcher.h"

DataFetcher::DataFetcher()
{

}

size_t DataFetcher::writeFunction(void* ptr, size_t size, size_t nmemb, std::string* d)
{
    d->append((char*) ptr, size * nmemb);
    return (size * nmemb);
}

std::string* DataFetcher::getData(const std::string& URL)
{
    CURL *curl;
    CURLcode res;
    std::string* data = new std::string();

    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
        // curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");     /**< Sometimes neeed */

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "X-Auth-Token: your_very_own_access_token");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return data;
}
