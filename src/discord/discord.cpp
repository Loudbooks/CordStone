//
// Created by Loudbook on 10/11/24.
//

#include "discord.h"

void Discord::connect(const std::string& token) {
    try {
        this->cluster = std::make_unique<dpp::cluster>(token);
    } catch (const std::exception& e) {
        std::cerr << "Failed to connect to Discord: " << e.what() << std::endl;
    }
}

void Discord::sendFormattedEmbed(const std::string &content, const MessageType type, const std::string& username, const std::string& uuid) const {
    dpp::embed embed;
    embed.set_thumbnail("https://api.tydiumcraft.net/v1/players/skin?uuid=" + uuid + "&type=avatar");

    switch (type) {
        case MessageType::JOIN:
            embed.title = username + " has joined the server!";
            embed.color = 0x00FF00;
            embed.description = content;
            break;
        case MessageType::LEAVE:
            embed.title = username + " has left the server!";
            embed.color = 0xFF0000;
            embed.description = content;
            break;
        case MessageType::MESSAGE:
            embed.title = username;
            embed.color = 0x0000FF;
            embed.description = content;
            break;
        case MessageType::START:
            embed.title = "Server started!";
            embed.color = 0x00FF00;
            embed.description = content;
            break;
        case MessageType::STOP:
            embed.title = "Server stopped!";
            embed.color = 0xFF0000;
            embed.description = content;
            break;

        default: break;
    }

    this->sendEmbed(embed);
}


void Discord::sendMessage(const std::string& message) const {
    auto dppMessage = dpp::message();
    dppMessage.content = message;
    dppMessage.set_channel_id(this->channelId);

    executeSend(dppMessage);
}

void Discord::sendEmbed(const dpp::embed& embed) const {
    auto dppMessage = dpp::message();
    dppMessage.embeds.push_back(embed);
    dppMessage.set_channel_id(this->channelId);

    executeSend(dppMessage);
}

void Discord::executeSend(const dpp::message& message) const {
    try {
        this->cluster->message_create(message);
    } catch (const std::exception& e) {
        std::cerr << "Failed to send message: " << e.what() << std::endl;
    }
}