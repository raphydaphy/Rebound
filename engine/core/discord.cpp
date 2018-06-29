#include "discord.hpp"

// Discord dosen't use a namespace
#include "discord_rpc.h"

static constexpr char CLIENT_ID[] = "462169497747587074";

namespace core
{
    void initDiscord()
    {
        DiscordEventHandlers handlers;
        memset(&handlers, 0, sizeof(handlers));
        // handlers are function pointers for callbacks...
        Discord_Initialize(CLIENT_ID, &handlers, 1, nullptr);

        // set a basic presence
        DiscordRichPresence presence;
        memset(&presence, 0, sizeof(presence));
        presence.details = "Looking at trees";
        Discord_UpdatePresence(&presence);
    }

    void shutdownDiscord()
    {
        Discord_Shutdown();
    }
}