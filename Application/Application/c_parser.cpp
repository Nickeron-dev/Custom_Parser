#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <curl/curl.h>
#include <cstring>
#include <string>
#include "mainwindow.h"

const char *ERROR_SSL_MESSAGE = "SSL peer certificate or SSH remote key was not OK";

int Parser::parse_url(std::string url)
{
    CURL *curl;
    CURLcode result;

    curl = curl_easy_init();

    std::cout << "SITE: " << url << std::endl;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    FILE *output_file = fopen("index.html", "w");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);

    result = curl_easy_perform(curl);
    if(result != CURLE_OK)
    {
        if (strcmp(curl_easy_strerror(result), ERROR_SSL_MESSAGE) == 0)
        {
            std::cout << "Retry without ssl verifiers..." << std::endl;
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);
        }
        else
        {
            std::cerr << "curl_easy_perform() failed: "
                      << curl_easy_strerror(result) << std::endl;
            fclose(output_file);
            return EXIT_FAILURE;
        }
    }

    result = curl_easy_perform(curl);

    if(result != CURLE_OK)
    {
        std::cerr << "curl_easy_perform() failed: "
                  << curl_easy_strerror(result) << std::endl;
        fclose(output_file);
        return EXIT_FAILURE;
    }

    curl_easy_cleanup(curl);
    fclose(output_file);
    std::cout << "Success!!!" << std::endl;
    return EXIT_SUCCESS;
}
