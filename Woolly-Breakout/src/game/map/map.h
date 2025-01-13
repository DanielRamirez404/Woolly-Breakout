#pragma once
#include "../entities/player.h"
#include "../entities/safe-zone.h"
#include "utilities.h"
#include "../../constants/constants.h"
#include <array>
#include <optional>
#include <string>
#include <queue>
#include <utility>
#include <functional>

class Map {

	public:

		enum Event {
			PickUpKey,
			Win,
			Quit,
		};

		Map(bool isSinglePlayer = true);

		using Matrix = std::array<std::array<char, Constants::Map::Matrix::size>, Constants::Map::Matrix::size>;
		
		int getPickedUpKeys() const;
		bool isSafeZoneOpen() const;
		bool isLegalMove(const Coordinates<int>& coordinates) const;

		void handlePlayerInteractions(Player& handledPlayer, const std::function<void()>& onWin);

		bool isThereAnyEvent();
		std::pair<Event, std::string> getFirstEvent();
		void addEvent(const std::pair<Event, std::string>& event);

		void handlePickingKeyUp(std::string& eventString);
		void handlePickingKeyUp(const Coordinates<int>& coordinates);
		
		std::string toString();
		void readString(std::string& string);

		Player& getPlayer();
		const Player& getPlayer() const;
		Player& getSecondPlayer();
		const Player& getSecondPlayer() const;

		const char operator()(int i, int j) const;
		static bool isOutOfBounds(int i, int j);

	private:

		Matrix matrix{
			{
				{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
				{'0', '1', '1', '1', '0', '1', '0', '0', '0', '0'},
				{'0', '0', '3', '1', '0', '0', '0', '0', '1', '0'},
				{'1', '1', '1', '1', '1', '0', '1', '0', '1', '0'},
				{'0', '3', '1', '0', '0', '0', '1', '0', '1', '0'},
				{'0', '1', '1', '0', '3', '0', '1', '0', '1', '3'},
				{'0', '1', '0', '0', '0', '0', '1', '0', '1', '0'},
				{'0', '1', '0', '0', '0', '0', '1', '0', '1', '1'},
				{'0', '0', '0', '1', '1', '0', '1', '0', '1', '1'},
				{'1', '3', '1', '0', '0', '0', '0', '2', '0', '1'},
			}
		};

		Player player{ Coordinates<int>{ 0, 5 } };
		std::optional<Player> secondPlayer{ std::nullopt };
		std::optional<SafeZone> safeZone{ std::nullopt };

		void handleWinCheking(const Coordinates<int>& coordinates, const std::function<void()>& onWin);

		std::queue<std::pair<Event, std::string>> events{};
};
