//
// Created by Loudbook on 10/11/24.
//

// ReSharper disable CppMemberFunctionMayBeConst
#pragma once
#include <endstone/plugin/plugin.h>
#include <endstone/event/player/player_join_event.h>
#include <endstone/event/player/player_quit_event.h>
#include <endstone/event/player/player_chat_event.h>

#include "discord/discord.h"
#include "json/json_loader.h"
#include "minecraft/image_uploader.h"

class CordStone : public endstone::Plugin {
public:
    CordStone() : loader(JsonLoader(std::filesystem::current_path().string() + "/CordStone/config.json")), discord(loader.getChannelId(), ImageUploader("https://bedrock.loudbook.dev/upload")) {}

private:
    void onEnable() override {
        registerEvent(&CordStone::onPlayerJoin, *this);
        registerEvent(&CordStone::onPlayerQuit, *this);
        registerEvent(&CordStone::onPlayerChat, *this);

        discord.connect(loader.getToken());

        discord.sendFormattedEmbed("Server started.", MessageType::START, "", "");
    }

    void onDisable() override {
        discord.sendFormattedEmbed("Server stopped.", MessageType::STOP, "", "");
    }

    void onPlayerJoin(const endstone::PlayerJoinEvent& event) {
        discord.sendFormattedEmbed(event.getPlayer().getName() + " joined the server.", MessageType::JOIN, event.getPlayer().getSkin().getSkinData().data, event.getPlayer().getName());
    }

    void onPlayerQuit(const endstone::PlayerQuitEvent& event) {
        discord.sendFormattedEmbed(event.getPlayer().getName() + " left the server.", MessageType::LEAVE, event.getPlayer().getSkin().getSkinData().data, event.getPlayer().getName());
    }

    void onPlayerChat(const endstone::PlayerChatEvent& event) {
        discord.sendFormattedEmbed(event.getMessage(), MessageType::MESSAGE, event.getPlayer().getSkin().getSkinData().data, event.getPlayer().getName());
    }

    JsonLoader loader;
    Discord discord;
};
