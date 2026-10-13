/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GasterManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:39:30 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/13 10:08:18 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <memory>

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
# include "protocol/TCP_error.hpp"
# include "utils/colored_text.h"
# include "utils.h"
# include "debug.h"


// --- CONSTRUCTOR ---
GasterManager::GasterManager(
	WorldConfig& world_data
):
	_world_data(world_data) {

		// Create all the objects
		createRoom();
		createEntities();
		createItems();
		// Fill the rooms data
		fillRoomsData();
	}

// ===== PUBLIC =====
// --- PLAYER MANAGEMENTS ---
// CREATE PLAYER
void	GasterManager::createPlayer(const std::string& player_name) {
	auto new_player = std::make_unique<Player>(player_name);
	new_player->setZone(_world_state.rooms["spawn"]->getID());
	_world_state.players[player_name] = std::move(new_player);
	_world_state.rooms["spawn"]->addPlayer(_world_state.players[player_name].get());

	print_log("GasterManager: player '" + player_name + "' spawned in " + _world_state.players[player_name]->getZone() + ".\n");
}

// --- GETTER ---
// *Get a formatted list of players in game. *
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

	return "Players Connected: " + std::to_string(nb_players) + ":\n" + list_players + "\n";
}

// *Get the data of the current room of the player.*
const std::string	GasterManager::getRoomData(const std::string& player_name) const {
	// Get the zone of the player
	std::string	zone_player = getPlayerRoom(player_name);

	// Get the data of the room
	std::string room_data = _world_state.rooms.at(zone_player)->getRoomData();
	return room_data;
}

// *Get the room of of the player.*
const std::string	GasterManager::getPlayerRoom(const std::string& player_name) const {
	// Find the player
	auto player = _world_state.players.find(player_name);
	if (player == _world_state.players.end()) {
		print_log("GasterManager: can't find player to give room state.");
		return "";
	}

	// Get the room of the player
	std::string	zone_player = player->second->getZone();
	if (zone_player.empty() || _world_state.rooms.find(zone_player) == _world_state.rooms.end()) {
		print_log("GasterManager: can't find the zone of player '" + player_name + "'.");
		return "";
	}
	return zone_player;
}

// --- MOVEMENT ---
// *Move a player to a direction. Take a player name and a Direction.*
bool	GasterManager::movePlayer(const std::string& player_name, const Direction direction) {
	// Get the zone of the player
	std::string	zone_player = getPlayerRoom(player_name);

	// get player
	auto player = _world_state.players.find(player_name);

	// Get the direction from the room
	Room* new_room = _world_state.rooms[zone_player]->getFromDirection(direction);
	if (new_room == nullptr) {
		print_log("GasterManager: bad direction '" + direction_to_string(direction)  + "' " + "for zone '" + zone_player + "'.");
		return false;
	}

	// Move the player (delete it from the room and add it to the new one)
	_world_state.rooms[zone_player]->popPlayer(player_name);
	new_room->addPlayer(player->second.get());
	player->second->setZone(new_room->getID());
	print_log("GasterManager: moved player '" + player_name + "' from '" + zone_player + "' to '" + new_room->getName() + "'.");
	return true;
}

// --- CHECKER ---
// * Check if the user exist, return true if yes. *
bool	GasterManager::checkIfUserExist(const std::string& username) const {
	auto search = _world_state.players.find(username);
	if (search != _world_state.players.end()) {
		return true;
	}
	return false;
}

// ===== PRIVATE =====
// --- OBJECTS MANAGEMENTS ---
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
					entity_id, entity.name, entity.description, entity.dialogue, entity.type, entity.hp);
				break;

			case EnemyType::BOSS:
				new_entity = std::make_unique<Boss>(
					entity_id, entity.name, entity.description, entity.dialogue, entity.type, entity.hp);
				break;

			case EnemyType::NPC:
				new_entity = std::make_unique<NPC>(
					entity_id, entity.name, entity.description, entity.dialogue, entity.type, entity.hp);
				break;

			case EnemyType::SHOP:
				new_entity = std::make_unique<NPCShop>(
					entity_id, entity.name, entity.description, entity.dialogue, entity.type, entity.hp);
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

// --- DEBUG ---
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
		std::cout << _world_state.rooms["spawn"]->getRoomData() << "\n\n";

		std::cout << RED << "Try to move player to an bad direction: \n" << RESET;
		movePlayer(test_player, Direction::NORTH);
		std::cout << _world_state.rooms["spawn"]->getRoomData() << "\n\n";

		std::cout << RED << "Try to move player to an good direction: \n" << RESET;
		if (!movePlayer(test_player, Direction::EAST)) {
			return;
		}
		std::cout << _world_state.rooms["spawn"]->getRoomData() << "\n\n";
		Room* room_east = _world_state.rooms["spawn"]->getFromDirection(Direction::EAST);
		if (room_east != nullptr) {
			std::cout << _world_state.rooms[room_east->getID()]->getRoomData() << "\n\n";
		}
	}
}
