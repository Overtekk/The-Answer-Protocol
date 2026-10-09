/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GasterManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:39:30 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 15:01:42 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <memory>

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
		create_room();
		create_entities();
		create_items();
		// Fill the rooms data
		fill_rooms_data();
	}

// ===== PUBLIC =====
// --- PLAYER MANAGEMENTS ---
// CREATE PLAYER
void	GasterManager::create_player(const std::string& player_name) {
	auto new_player = std::make_unique<Player>(player_name);
	new_player->setZone(_world_state.rooms["spawn"]->getName());
	_world_state.players[player_name] = std::move(new_player);

	print_log("GasterManager: player '" + player_name + "' spawned in " + _world_state.players[player_name]->getZone() + ".\n");
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
void	GasterManager::create_room() {
	for (const auto& [loc_id, loc] : _world_data.locations) {
		auto new_room = std::make_unique<Room>(
			loc.name, loc.description, loc.tile_map, loc.special
		);
		_world_state.rooms[loc_id] = std::move(new_room);
	}
}

// * Create the entities and add them to the world state. *
void	GasterManager::create_entities() {
	for (const auto& [entity_id, entity] : _world_data.entities) {
		std::unique_ptr<Entity> new_entity;

		switch (entity.type) {
			case EnemyType::ENEMY:
				new_entity = std::make_unique<Enemy>(
					entity.name, entity.description, entity.dialogue, entity.type, entity.hp);
				break;

			case EnemyType::BOSS:
				new_entity = std::make_unique<Boss>(
					entity.name, entity.description, entity.dialogue, entity.type, entity.hp);
				break;

			case EnemyType::NPC:
				new_entity = std::make_unique<NPC>(
					entity.name, entity.description, entity.dialogue, entity.type, entity.hp);
				break;

			case EnemyType::SHOP:
				new_entity = std::make_unique<NPCShop>(
					entity.name, entity.description, entity.dialogue, entity.type, entity.hp);
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
void	GasterManager::create_items() {
	for (const auto& [item_id, item] : _world_data.items) {
		std::unique_ptr<Item> new_item;

		switch (item.type) {
			case ItemType::CONSUMABLE:
				new_item = std::make_unique<ItemConsumable>(
					item.name, item.description, item.type, item.damage, item.hp);
				break;

			case ItemType::KEY:
				new_item = std::make_unique<ItemKey>(
					item.name, item.description, item.type, item.damage, item.hp);
				break;

			case ItemType::WEAPON:
				new_item = std::make_unique<ItemWeapon>(
					item.name, item.description, item.type, item.damage, item.hp);
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
void	GasterManager::fill_rooms_data() {
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
void	GasterManager::debug_print_structure_data(bool show_gui_data) {
	debug_print_structure(_world_data, show_gui_data);
}

// Print the structure of WorldState
void	GasterManager::debug_print_structure_state() {
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
