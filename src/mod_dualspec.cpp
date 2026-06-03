/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 *
 * Adds the .dualspec player command, which unlocks Dual Talent
 * Specialization for the calling character. Mirrors the unlock
 * pathway used by mod-npc-services (Learn Dual Talents gossip option).
 */

#include "ScriptMgr.h"
#include "Configuration/Config.h"
#include "Chat.h"
#include "ChatCommand.h"
#include "Player.h"

using namespace Acore::ChatCommands;

class dualspec_commandscript : public CommandScript
{
public:
    dualspec_commandscript() : CommandScript("dualspec_commandscript") { }

    ChatCommandTable GetCommands() const override
    {
        static ChatCommandTable dualspecCommandTable =
        {
            { "dualspec", HandleDualspecCommand, SEC_PLAYER, Console::No },
        };
        return dualspecCommandTable;
    }

    static bool HandleDualspecCommand(ChatHandler* handler, char const* /*args*/)
    {
        if (!sConfigMgr->GetOption<bool>("DualSpec.Enable", true))
        {
            handler->SendSysMessage("|cffFF0000The .dualspec command is currently disabled on this server.|r");
            return true;
        }

        Player* player = handler->GetSession() ? handler->GetSession()->GetPlayer() : nullptr;
        if (!player)
            return false;

        if (player->IsInCombat())
        {
            handler->SendSysMessage("|cffFF0000You cannot use .dualspec while in combat.|r");
            return true;
        }

        if (player->GetSpecsCount() >= 2)
        {
            handler->SendSysMessage("|cffFFFF00You already have Dual Talent Specialization unlocked.|r");
            return true;
        }

        // Hardcoded: talent points are awarded starting at level 10, so dual
        // spec is meaningless (and broken) below that.
        if (player->GetLevel() < 10)
        {
            handler->SendSysMessage("|cffFF0000You must be at least level 10 to use .dualspec.|r");
            return true;
        }

        player->learnSpell(63644);
        player->CastSpell(player, 31726, true);
        player->CastSpell(player, 63624, true);
        player->learnSpell(63645);
        player->UpdateSpecCount(2);

        handler->SendSysMessage("|cff4CFF00Dual Talent Specialization unlocked!|r");
        return true;
    }
};

void AddDualSpecCommandScripts()
{
    new dualspec_commandscript();
}
