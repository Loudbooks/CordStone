//
// Created by Loudbook on 10/11/24.
//

#include "image_uploader.h"

#include <curl/curl.h>
#include <iostream>

ImageUploader::ImageUploader(std::string serverUrl) : serverUrl(std::move(serverUrl)) {}

void ImageUploader::upload(const std::string& imageData, const std::string& imageName) const {
    std::string response;

    if(CURL *curl = curl_easy_init()) {
        curl_mime *mime = curl_mime_init(curl);

        curl_mimepart *part = curl_mime_addpart(mime);
        curl_mime_data(part, imageData.c_str(), imageData.size());
        curl_mime_type(part, "image/jpeg");
        curl_mime_filename(part, imageName.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, serverUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char* ptr, size_t size, size_t nmemb, std::string* data) -> size_t {
            data->append(ptr, size * nmemb);
            return size * nmemb;
        });

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        if(const CURLcode res = curl_easy_perform(curl); res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_mime_free(mime);
        curl_easy_cleanup(curl);
    }

    std::cout << response << std::endl;
}
