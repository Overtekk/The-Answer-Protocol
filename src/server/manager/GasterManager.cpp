/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GasterManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:39:30 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/29 09:45:19 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <memory>
#include <optional>
# include <utility>
# include <string>
# include <unordered_map>

# include <nlohmann/json.hpp>
# include "server/manager/GasterManager.hpp"
# include "base_class/rooms/Room.hpp"
# include "base_class/entities/Player.hpp"
# include "base_class/entities/Entity.hpp"
# include "base_class/entities/Enemy.hpp"
# include "base_class/entities/Boss.hpp"
# include "base_class/entities/NPC.hpp"
# include "base_class/entities/NPCShop.hpp"
# include "base_class/items/Item.hpp"
# include "base_class/items/ItemWeapon.hpp"
# include "base_class/items/ItemKey.hpp"
# include "base_class/items/ItemConsumable.hpp"
# include "core/QuestManager.hpp"
# include "core/DialogueManager.hpp"
# include "config/WorldConfig.hpp"
# include "config/WorldState.hpp"
# include "config/Enums.hpp"
# include "utils/colored_text.h"
# include "utils.h"
# include "debug.h"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
GasterManager::GasterManager(WorldConfig& world_data):
	_world_data(world_data),
	_quest_manager(_world_data.quests),
	_dialogue_manager(_world_data.entities) {

		// Create all the objects
		createRoom();
		createEntities();
		createItems();
		// Fill the rooms data
		fillRoomsData();
	}

// ============================================================================
// =========================       PUBLIC      ================================
// ============================================================================
// CREATE PLAYER
void	GasterManager::createPlayer(const std::string& player_name) {
	// Get the spawn zone
	Room* spawn = _world_state.rooms["spawn"].get();

	// Create the player
	auto new_player = std::make_unique<Player>(player_name);

	// Place the player in the spawn
	new_player->setZone(spawn->getID());
	Player* player = new_player.get();
	_world_state.players[player_name] = std::move(new_player);
	spawn->addPlayer(player);

	// Give the player the default quests
	_quest_manager.addDefaultQuests(*player);

	print_log("GasterManager: player '" + player_name + "' spawned in " + _world_state.players[player_name]->getZone() + ".\n");
}

// ============================================================================
// ===================      COMMANDS - GETTER      ============================
// ============================================================================
// * Get a formatted list of players in game. *
const std::string	GasterManager::getListOfPlayers() const {
	std::string	list_players = "[";

	int	nb_players = 0;
	for (const auto& it : _world_state.players) {
		list_players += it.first + ", ";
		nb_players++;
	}

	if (nb_players == 0) {
		list_players = "[]";
	}
	else {
		list_players.pop_back();
		list_players.pop_back();
		list_players += "]";
	}

	return "Players Connected: " + std::to_string(nb_players) + ": " + list_players;
}

// * Get the data of the current room of the player.*
const std::string	GasterManager::getRoomData(const std::string& player_name, bool add_details) const {
	// Get the zone of the player
	std::string zone_player = getPlayerRoom(player_name);
	if (zone_player.empty())
		return "ERROR: Player room not found.\n";

	return _world_state.rooms.at(zone_player)->getRoomData(add_details);
}

// * Get the room of of the player.*
const std::string	GasterManager::getPlayerRoom(const std::string& player_name) const {
	// Find the player
	const Player* player = getPlayer(player_name);
	if (!player)
		return "Player not found";

	// Get the room of the player
	const std::string& zone_player = player->getZone();
	if (zone_player.empty() || _world_state.rooms.find(zone_player) == _world_state.rooms.end()) {
		print_log("GasterManager: can't find the zone of player '" + player_name + "'.");
		return "\n";
	}
	return zone_player;
}

// * Get the inventory of a player. *
const std::string	GasterManager::getPlayerInventory(const std::string& player_name, bool add_details) const {
	const Player* player = getPlayer(player_name);
	if (!player)
		return "Player not found";

	return player->getItemInInventory(add_details);
}

// * Get the quests of a player. *
const std::string	GasterManager::getPlayerQuests(const std::string& player_name) const {
	const Player* player = getPlayer(player_name);
	if (!player)
		return "Player not found";

	std::string str_list_quests = "[";

	for (const std::string& act_quests :   player->getCurrentQuests()) {
		str_list_quests += "{\"quest_id\": \"" + act_quests + "\", \"status\": \"";
		str_list_quests += quest_state_to_string(player->getQuestStatut(act_quests)) + "\"}, ";
	}

	for (const std::string& cmplt_quests :  player->getCompletedQuests()) {
		str_list_quests += "{\"quest_id\": \"" + cmplt_quests + "\", \"status\": \"";
		str_list_quests += quest_state_to_string(player->getQuestStatut(cmplt_quests)) + "\"}, ";
	}

	if (str_list_quests.size() > 1)
		str_list_quests.erase(str_list_quests.size() - 2);
	str_list_quests += "]";

	return str_list_quests;

}

// * Get the name and description of a quest. *
const std::string	GasterManager::getQuestDescription(const std::string& player_name, const std::string& quest_id) const {
	const Player* player = getPlayer(player_name);
	if (!player)
		return "Player not found";

	if (player->getQuestStatut(quest_id) == QuestState::NOT_FOUND)
		return "Quest not found.";

	std::unordered_map<std::string, std::string> quest_info = _quest_manager.getQuestInformation(quest_id);
	if (quest_info.empty())
		return "Quest not found.";

	return "quest name: \"" + quest_info["name"] + "\", quest description: \"" + quest_info["description"] + "\"";
}

// ============================================================================
// ===================      COMMANDS - DIALOGUE      ==========================
// ============================================================================
// * Get the dialogue line and send it to the client. *
const std::string	GasterManager::getDialogue(const std::string& player_name, const std::string& entity_id) {
	Player* player = getPlayer(player_name);
	if (!player)
		return "Player not found.";

	const Entity* entity = getEntity(entity_id);
	if (!entity)
		return "Entity not found.";

	// Get the room of the player
	Room* player_room = getRoom(player->getZone());
	if (!player_room)
		return "Can't find player room";
	// Check if entity is in player room
	Entity* entity_in_room = player_room->getEntity(entity->getName());
	if (!entity_in_room)
		return "Entity not in player room";

	int dialogue_index = player->getDialogueIndex(entity_id);
	if (_dialogue_manager.hasKey(entity_id, "talk_" + std::to_string(dialogue_index + 1))) {
		std::optional<std::string> dialogue = _dialogue_manager.getLine(entity_id, "talk_" + std::to_string(dialogue_index + 1));
		return dialogue;
	}
	return "It doesn't want to speak.";
}

// ============================================================================
// ===================      COMMANDS - MOVEMENTS      =========================
// ============================================================================
// *Move a player to a direction. Take a player name and a Direction.*
bool	GasterManager::movePlayer(const std::string& player_name, const Direction direction) {
	// Get player
	Player* player = getPlayer(player_name);
	if (!player)
		return false;

	// Get the zone of the player
	const std::string& zone_player = player->getZone();
	auto room_it = _world_state.rooms.find(zone_player);
	if (zone_player.empty() || room_it == _world_state.rooms.end()) {
		print_log("GasterManager: can't find zone '" + zone_player + "'.");
		return false;
	}

	// Get the direction
	Room* current_room = room_it->second.get();
	Room* new_room = current_room->getFromDirection(direction);
	if (!new_room) {
		print_log("GasterManager: bad direction '" + direction_to_string(direction) + "' for zone '" + zone_player + "'.");
		return false;
	}

	// Move the player
	current_room->popPlayer(player_name);
	new_room->addPlayer(player);
	player->setZone(new_room->getID());

	print_log("GasterManager: moved player '" + player_name + "' from '" + zone_player + "' to '" + new_room->getName() + "'.");
	return true;
}

// * Take a requested item and put in player inventory. *
bool	GasterManager::takeItem(const std::string& player_name, const std::string& item_name) {
	// Get the player
	Player*	player = getPlayer(player_name);
	if (!player)
		return false;
	// Get the room of the player
	Room* player_room = getRoom(player->getZone());
	if (!player_room)
		return false;
	// Get the item requested
	Item* item = getItem(item_name);
	if (!item)
		return false;

	// Pop item from the room
	Item* item_room = player_room->popItem(item->getUniqueID());
	if (!item_room) {
		print_log("GasterManager: item '" + item_name + "' not in room.");
		return false;
	}

	// Add to inventory
	player->addItemToInventory(item_room);
	return true;
}

// * Drop a requested item and put in player inventory. *
bool	GasterManager::dropItem(const std::string& player_name, const std::string& item_name) {
	// Get the player
	Player*	player = getPlayer(player_name);
	if (!player)
		return false;
	// Get the room of the player
	Room* player_room = getRoom(player->getZone());
	if (!player_room)
		return false;
	// Get the item requested
	Item* item = getItem(item_name);
	if (!item)
		return false;

	// Pop item from player inventory
	Item *item_player = player->popItemFromInventory(item->getUniqueID());
	if (!item_player) {
		print_log("GasterManager: item '" + item_name + "' not in player inventory.");
		return false;
	}

	// Add to the room
	player_room->placeItem(item_player);
	return true;
}

// ============================================================================
// ===================           CHECKER      =================================
// ============================================================================
// * Check if the user exist, return true if yes. *
bool	GasterManager::checkIfUserExist(const std::string& username) const {
	return _world_state.players.find(username) != _world_state.players.end();
}

// ============================================================================
// =========================       PRIVATE      ===============================
// ============================================================================
// * Get a player (const). *
const Player*	GasterManager::getPlayer(const std::string& player_name) const {
	auto it = _world_state.players.find(player_name);
	if (it == _world_state.players.end()) {
		print_log("GasterManager: can't find player '" + player_name + "'.");
		return nullptr;
	}
	return it->second.get();
}

// * Get a player. *
Player* GasterManager::getPlayer(const std::string& player_name) {
    return const_cast<Player*>(std::as_const(*this).getPlayer(player_name));
}

// * Get an item (const). *
const Item*	GasterManager::getItem(const std::string& item_name) const {
	auto it = _world_state.items.find(item_name);
	if (it == _world_state.items.end()) {
		print_log("GasterManager: can't find item '" + item_name + "'.");
		return nullptr;
	}
	return it->second.get();
}

// * Get an item. *
Item* GasterManager::getItem(const std::string& item_name) {
	return const_cast<Item*>(std::as_const(*this).getItem(item_name));
}

// * Get a room (const). *
const Room*	GasterManager::getRoom(const std::string& room_id) const {
	auto it = _world_state.rooms.find(room_id);
	if (it == _world_state.rooms.end()) {
		print_log("GasterManager: can't find room '" + room_id + "'.");
		return nullptr;
	}
	return it->second.get();
}

// * Get a room. *
Room*	GasterManager::getRoom(const std::string& room_id) {
	return const_cast<Room*>(std::as_const(*this).getRoom(room_id));
}

// * Get an entity (const). *
const Entity*	GasterManager::getEntity(const std::string& entity_id) const {
	auto it = _world_state.entities.find(entity_id);
	if (it == _world_state.entities.end()) {
		print_log("GasterManager: can't find entity '" + entity_id + "'.");
		return nullptr;
	}
	return it->second.get();
}

// * Get an entity. *
Entity*	GasterManager::getEntity(const std::string& entity_id) {
	return const_cast<Entity*>(std::as_const(*this).getEntity(entity_id));
}

// ============================================================================
// ==================       OBJECTS MANAGEMENTS      ==========================
// ============================================================================
// CREATE OBJECTS
// * Create the rooms and add them to the world state. *
void	GasterManager::createRoom() {
	for (const auto& [loc_id, loc] : _world_data.locations) {
		auto new_room = std::make_unique<Room>(
			loc_id, loc.name, loc.description, loc.tile_map, loc.special
		);
		_world_state.rooms[loc_id] = std::move(new_room);
	}
}

// * Create the entities and add them to the world state. *
void	GasterManager::createEntities() {
	for (const auto& [entity_id, entity] : _world_data.entities) {
		std::unique_ptr<Entity> new_entity;

		switch (entity.type) {
			case EnemyType::ENEMY:
				new_entity = std::make_unique<Enemy>(
					entity_id, entity.name, entity.description, entity.type, entity.hp);
				break;

			case EnemyType::BOSS:
				new_entity = std::make_unique<Boss>(
					entity_id, entity.name, entity.description, entity.type, entity.hp);
				break;

			case EnemyType::NPC:
				new_entity = std::make_unique<NPC>(
					entity_id, entity.name, entity.description, entity.type, entity.hp);
				break;

			case EnemyType::SHOP:
				new_entity = std::make_unique<NPCShop>(
					entity_id, entity.name, entity.description, entity.type, entity.hp);
				break;

			default:
					continue;
		}

		if (new_entity) {
			_world_state.entities[entity_id] = std::move(new_entity);
		}
	}
}

// * Create the items and add them to the world state. *
void	GasterManager::createItems() {
	for (const auto& [item_id, item] : _world_data.items) {
		std::unique_ptr<Item> new_item;

		switch (item.type) {
			case ItemType::CONSUMABLE:
				new_item = std::make_unique<ItemConsumable>(
					item_id, item.name, item.description, item.type, item.damage, item.hp);
				break;

			case ItemType::KEY:
				new_item = std::make_unique<ItemKey>(
					item_id, item.name, item.description, item.type, item.damage, item.hp);
				break;

			case ItemType::WEAPON:
				new_item = std::make_unique<ItemWeapon>(
					item_id, item.name, item.description, item.type, item.damage, item.hp);
				break;

			default:
					continue;
		}

		if (new_item) {
			_world_state.items[new_item->getID()] = std::move(new_item);
		}
	}
}

// FILL OBJECTS
void	GasterManager::fillRoomsData() {
	for (const auto& [room_id, data] : _world_state.rooms) {
		auto loc = _world_data.locations.find(room_id);
		if (loc == _world_data.locations.end()) {
			continue;
		}
		const auto& config = loc->second;

		// Fill the exits
		for (const auto& [dir, target_id] : config.exits) {
			if (dir == Direction::NORTH) {
				data->setExitNorth(_world_state.rooms[target_id].get());
			}
			if (dir == Direction::SOUTH) {
				data->setExitSouth(_world_state.rooms[target_id].get());
			}
			if (dir == Direction::EAST) {
				data->setExitEast(_world_state.rooms[target_id].get());
			}
			if (dir == Direction::WEST) {
				data->setExitWest(_world_state.rooms[target_id].get());
			}
		}
		// Fill the items
		for (const auto& item : config.items) {
			data->placeItem(_world_state.items[item].get());
		}
		// Fill entities
		for (const auto& entity : config.spawns) {
			data->addEntity(_world_state.entities[entity].get());
		}
	}
}

// ============================================================================
// =========================       DEBUG      =================================
// ============================================================================
// Print the structure of WorldData
void	GasterManager::debugPrintStructureData(bool show_gui_data) {
	debug_print_structure(_world_data, show_gui_data);
}

// Print the structure of WorldState
void	GasterManager::debugPrintStructureState() {
	std::cout << RED << "ROOMS:\n" << RESET;
	for (const auto& [id, room] : _world_state.rooms) {
		std::cout << id << " is at " << room.get() << " and is named " << CYN << room->getName() << RESET << ".\n";
	}

	std::cout << RED << "ENTITIES:\n" << RESET;
	for (const auto& [id, entity] : _world_state.entities) {
		std::cout << id << " is at " << entity.get() << " and is named " << CYN << entity->getName() << RESET << " and his type is " << enemy_type_to_string(entity->getType()) << ".\n";
	}

	std::cout << RED << "ITEMS:\n" << RESET;
	for (const auto& [id, item] : _world_state.items) {
		std::cout << item->getID() << " is at " << item.get() << " and is named " << CYN << item->getName() << RESET << " and his type is " << item_type_to_string(item->getType()) << ".\n";
	}
}

void	GasterManager::debugTrySimulate(bool try_move) {
	std::string	test_player = "Nono la racaille";
	createPlayer(test_player);

	if (try_move) {
		std::cout << RED << "State of Spawn:\n" << RESET;
		std::cout << _world_state.rooms["spawn"]->getRoomData(false) << "\n\n";

		std::cout << RED << "Try to move player to an bad direction: \n" << RESET;
		movePlayer(test_player, Direction::NORTH);
		std::cout << _world_state.rooms["spawn"]->getRoomData(false) << "\n\n";

		std::cout << RED << "Try to move player to an good direction: \n" << RESET;
		if (!movePlayer(test_player, Direction::EAST)) {
			return;
		}
		std::cout << _world_state.rooms["spawn"]->getRoomData(false) << "\n\n";
		Room* room_east = _world_state.rooms["spawn"]->getFromDirection(Direction::EAST);
		if (room_east != nullptr) {
			std::cout << _world_state.rooms[room_east->getID()]->getRoomData(false) << "\n\n";
		}
	}
}
