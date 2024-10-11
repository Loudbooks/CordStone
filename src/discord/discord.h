//
// Created by Loudbook on 10/11/24.
//

#pragma once
#include <cluster.h>

#include <utility>

#include "message_type.hpp"

class Discord {
public:
    explicit Discord(std::string channel_id) : channelId(std::move(channel_id)) {}

    void connect(const std::string& token);

    void sendFormattedEmbed(const std::string &content, MessageType type, const std::string &username, const std::string &uuid) const;
private:
    void sendMessage(const std::string& message) const;

    void sendEmbed(const dpp::embed &embed) const;

    void executeSend(const dpp::message &message) const;

    std::unique_ptr<dpp::cluster> cluster;

    std::string channelId;
};
