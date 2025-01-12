#pragma once
#include "map/map.h"
#include "ui/elements.h"
#include "entities/player.h"
#include "ui/gameWindow.h"
#include "../networking/classes/host.h"
#include <string>
#include <optional>
#include <unordered_map>

class Game {
	public:

		Game(std::string prompt);

		enum Host {
			Server,
			Client,
			None,
		};

		void run();

	private:

		Host hostType{};
		std::optional<std::string> server_IPv4{};
		std::optional<Map> map{ std::nullopt };

		void startGame(bool isMultiplayer = false, bool isFirstPlayers = true);
		
		void hostGame();
		void joinGame();

		GameHost::MessageHandler runMultiplayerThreads(GameHost& host);
		std::string getNetworkingMessage(Player& player);
		void handleMessageReading(Player& player, std::string& message);

		void handleInput(Player& player, SDL::Event&);
		
		Player& getThisPlayer();
		Player& getTeammate();
};
