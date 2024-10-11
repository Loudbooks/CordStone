//
// Created by Loudbook on 10/11/24.
//

#include "json_loader.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>

using json = nlohmann::json;

JsonLoader::JsonLoader(const std::string &filePath) {
    if (std::ifstream file(filePath); !file.is_open()) {
        if (std::filesystem::path dir = std::filesystem::path(filePath).parent_path(); !exists(dir)) {
            create_directories(dir);

            std::cerr << "Created directories: " << dir << std::endl;
        }

        std::ofstream outFile(filePath);

        if (!outFile.is_open()) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            std::cerr << "Reason: " << std::strerror(errno) << std::endl;
            return;
        }

        json jsonObject;
        jsonObject["token"] = "YOUR DISCORD BOT TOKEN";
        jsonObject["channelId"] = "YOUR DISCORD CHANNEL ID";

        outFile << jsonObject.dump(4) << std::endl;
        outFile.close();

        std::cerr << "File created: " << filePath << " with default values." << std::endl;
    } else {
        json jsonData;
        file >> jsonData;

        token = jsonData["token"];
        channelId = jsonData["channelId"];

        if (token.empty() || channelId.empty()) {
            std::cerr << "Error: token or channelId is empty." << std::endl;
            return;
        }

        file.close();
    }
}

const std::string &JsonLoader::getToken() const {
    return token;
}

const std::string &JsonLoader::getChannelId() const {
    return channelId;
}