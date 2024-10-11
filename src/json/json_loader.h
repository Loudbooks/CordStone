//
// Created by Loudbook on 10/11/24.
//

#pragma once
#include <string>
#include <vector>

class JsonLoader {
    std::string token;
    std::string channelId;

public:
    explicit JsonLoader(const std::string& filePath);
    [[nodiscard]] const std::string& getToken() const;
    [[nodiscard]] const std::string& getChannelId() const;
};