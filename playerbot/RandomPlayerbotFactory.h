#ifndef _RandomPlayerbotFactory_H
#define _RandomPlayerbotFactory_H

#include "Common.h"
#include "PlayerbotAIBase.h"

class WorldPacket;
class Player;
class Unit;
class Object;
class Item;

using namespace std;

class RandomPlayerbotFactory
{
    public:
        RandomPlayerbotFactory(uint32 accountId);
		virtual ~RandomPlayerbotFactory() {}

	public:
        bool CreateRandomBot(uint8 cls, unordered_map<uint8, vector<string>>& names);
        static void CreateRandomBots();
        static void CreateRandomGuilds();
        static void CreateRandomArenaTeams();
        static string CreateRandomGuildName();
        static bool isAvailableRace(uint8 cls, uint8 race);
	private:
        string CreateRandomBotName(uint8 gender);
        static string CreateRandomArenaTeamName();

    private:
        uint32 accountId;
        static map<uint8, vector<uint8> > availableRaces;
};

#endif
