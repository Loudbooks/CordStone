//
// Created by Loudbook on 10/11/24.
//

#pragma once
#include <cluster.h>

#include <utility>
#include <endstone/skin.h>
#include <endstone/actor/actor.h>

#include "message_type.hpp"
#include "../minecraft/image_uploader.h"

class Discord {
public:
    explicit Discord(std::string channel_id, ImageUploader image_uploader) : channelId(std::move(channel_id)), imageUploader(std::move(image_uploader)) {}

    void connect(const std::string& token);

    void sendFormattedEmbed(const std::string &content, MessageType type, const std::string& skin, const std::string &username) const;
private:
    void sendMessage(const std::string& message) const;

    void sendEmbed(const dpp::embed &embed) const;

    void executeSend(const dpp::message &message) const;

    std::unique_ptr<dpp::cluster> cluster;

    std::string channelId;

    ImageUploader imageUploader;
};
