//
// Created by Loudbook on 10/11/24.
//

#pragma once
#include <string>

class ImageUploader {
public:
    explicit ImageUploader(std::string  serverUrl);
    [[nodiscard]] std::string upload(const std::string& imageData, const std::string& imageName) const;

private:
    std::string serverUrl;
};
