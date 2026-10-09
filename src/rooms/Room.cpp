/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 11:59:13 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/09 13:40:26 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <filesystem>
# include <unordered_map>
# include <vector>

# include <nlohmann/json.hpp>
# include "base_class/rooms/Room.hpp"
# include "config/Enums.hpp"
# include "utils.h"

namespace fs = std::filesystem;


Room::Room(
	const std::string& id, const std::string& name, const std::string& description,
	const fs::path& background, const bool special
):
	_id(id),
	_name(name),
	_description(description),
	_background(background),
	_special(special)
	{
		this->_exits[Direction::NORTH] = nullptr;
		this->_exits[Direction::SOUTH] = nullptr;
		this->_exits[Direction::EAST] = nullptr;
		this->_exits[Direction::WEST] = nullptr;
	}

// ============================================================================
// =========================        DATA      =================================
// ============================================================================

nlohmann::json	Room::getRoomData() {
	nlohmann::json	room_data;

	room_data[_id]["id"] = this->getID();
	room_data[_id]["name"] = this->getName();
	room_data[_id]["description"] = this->getDescription();
	if (this->getFromDirection(Direction::NORTH) != nullptr) {
		room_data[_id]["exits"]["north"] = this->getFromDirection(Direction::NORTH)->getID();
	}
	if (this->getFromDirection(Direction::SOUTH) != nullptr) {
		room_data[_id]["exits"]["south"] = this->getFromDirection(Direction::SOUTH)->getID();
	}
	if (this->getFromDirection(Direction::EAST) != nullptr) {
		room_data[_id]["exits"]["east"] = this->getFromDirection(Direction::EAST)->getID();
	}
	if (this->getFromDirection(Direction::WEST) != nullptr) {
		room_data[_id]["exits"]["west"] = this->getFromDirection(Direction::WEST)->getID();
	}
	// List of players
	std::vector<std::string>	list_players;
	for (const auto& it : _players) {
		list_players.push_back(it.second->getName());
	}
	room_data[_id]["players"] = list_players;
	// List of items
	std::vector<std::string>	list_items;
	for (const auto& it : _items) {
		list_items.push_back(it.second->getID());
	}
	room_data[_id]["players"] = list_items;
	// List of npcs
	std::vector<std::string>	list_npcs;
	for (const auto& it : _npc) {
		list_npcs.push_back(it.second->getID());
	}
	room_data[_id]["players"] = list_npcs;

	return room_data;
}

// ============================================================================
// ===========================       ID      ==================================
// ============================================================================

const std::string&	Room::getID() const { return _id; }


// ============================================================================
// ===========================      NAME      =================================
// ============================================================================

std::string	Room::getName() const {
	return (this->_name);
}

bool	Room::setName(const std::string& new_name) {
	if (new_name.length() >= 3 && new_name.length() <= 20) {
		this->_name = new_name;
		return (true);
	}
	sendObjectError("Can't modify name. Minimum 3 and maximum 20 characters.");
	return (false);
}

// ============================================================================
// ===========================      DESC      =================================
// ============================================================================

std::string	Room::getDescription() const {
	return (this->_description);
}

bool	Room::setDescription(const std::string& new_desc) {
	if (new_desc.length() >= 5 && new_desc.length() <= 50)
	{
		this->_description = new_desc;
		return (true);
	}
	sendObjectError("Can't modify desc. Minimum 3 and maximum 20 characters.");
	return (false);
}

// ============================================================================
// ===========================      TEXTURE      ==============================
// ============================================================================

fs::path	Room::getBGTexturePath() const {
	return (this->_background);
}

// ============================================================================
// ===========================      PLAYER      ===============================
// ============================================================================

bool	Room::addPlayer(Player* player) {
	if (player == nullptr) {
		this->sendObjectError("Player's pointer point to null");
		return (false);
	}

	const std::string name = player->getName();
	if (this->_players.count(name) == 1) {
		this->sendObjectError("Player already in room");
		return (false);
	}
	this->_players[name] = player;
	return (true);
}

Player*	Room::popPlayer(const std::string& name) {
	if (this->_players.count(name) == 1)
	{
		Player  *player = this->_players[name];
		this->_players.erase(name);
		return (player);
	}
	this->sendObjectError("Invalide player name key (Player not in room)");
	return (nullptr);
}

Player*	Room::getPlayer(const std::string& name) {
	if (this->_players.count(name) == 1) {
		return (this->_players[name]);
	}
	this->sendObjectError("Invalide player name key (Player not in room)");
	return (nullptr);
}

// ============================================================================
// =============================   npc   ======================================
// ============================================================================

bool	Room::addNPC(NPC* npc) {
	if (npc == nullptr)
	{
		this->sendObjectError("npc's pointer point to null");
		return (false);
	}

	const std::string name = npc->getName();
	if (this->_npc.count(name) == 1)
	{
		this->sendObjectError("npc already in room");
		return (false);
	}
	this->_npc[name] = npc;
	return (true);
}

NPC*	Room::popNPC(const std::string& name) {
	if (this->_npc.count(name) == 1)
	{
		NPC  *npc = this->_npc[name];
		this->_npc.erase(name);
		return (npc);
	}
	this->sendObjectError("Invalide npc name key (npc not in room)");
	return (nullptr);
}

NPC*	Room::getNPC(const std::string& name) {
	if (this->_npc.count(name) == 1)
		return (this->_npc[name]);
	this->sendObjectError("Invalide npc name key (npc not in room)");
	return (nullptr);
}

// ============================================================================
// ============================      ITEMS      ===============================
// ============================================================================

bool	Room::placeItem(Item* item) {
	if (item == nullptr)
	{
		this->sendObjectError("Item's pointer point to null");
		return (false);
	}
	ItemID  item_id = item->getUniqueID();
	if (this->_items.count(item_id) == 1)
	{
		this->sendObjectError("Exact item already in room");
		return (false);
	}
	this->_items[item_id] = item;
	return (true);
}

Item*	Room::popItem(ItemID item_id) {
	if (this->_items.count(item_id) == 1)
	{
		Item*   item = this->_items[item_id];
		this->_items.erase(item_id);
		return (item);
	}
	this->sendObjectError("Invalide item name key (item not in room)");
	return (nullptr);
}

Item*	Room::getItem(ItemID item_id) {
	if (this->_items.count(item_id) == 1)
		return (this->_items[item_id]);
	this->sendObjectError("Invalide item name key (item not in room)");
	return (nullptr);
}

// ============================================================================
// ============================      ITEMS      ===============================
// ============================================================================

void	Room::setExitNorth(Room* room) {
	this->_exits[Direction::NORTH] = room;
}

void	Room::setExitSouth(Room* room) {
	this->_exits[Direction::SOUTH] = room;
}

void	Room::setExitEast(Room* room) {
	this->_exits[Direction::EAST] = room;
}

void	Room::setExitWest(Room* room) {
	this->_exits[Direction::WEST] = room;
}

void	Room::setExitUnknown(Room* room) {
	this->_exits[Direction::UNKNOWN] = room;
}

Room*	Room::getFromDirection(Direction direction) {
	return (this->_exits[direction]);
}

// ============================================================================
// =======================      Special stats      ============================
// ============================================================================
bool	Room::isSpecial() const {
	return (this->_special);
}


void	Room::sendObjectError(const std::string& error) const {
	print_log(" ERROR: " + error + "\n");
}
