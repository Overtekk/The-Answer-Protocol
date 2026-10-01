/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 23:35:41 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/01 16:30:07 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <yaml-cpp/yaml.h>
# include "utils.h"
# include "config/WorldConfig.hpp"

LocationConfig parse_locationConfig(const std::string& loc_id, const YAML::Node& node);
ItemConfig parse_itemConfig(const std::string& item_id, const YAML::Node& node);
EntityConfig parse_entityConfig(const std::string& entity_id, const YAML::Node& node);
Direction convert_direction(const std::string& direction_str);
ItemType convert_itemType(const std::string& itemtype_str);
EnemyType convert_enemyType(const std::string& enemytype_str);
void check_global_data_validation(const std::string& name, const std::string& desc, const std::string& id);
void check_int(int value, const std::string& id);


// --- TEMPLATE ---
// Safely extracts a typed value from a YAML node with fallback to defaultValue on error or missing key.
template <typename T>
T getValue(const YAML::Node& parent, const std::string& key, const T& defaultValue) {
	if (parent[key] && parent[key].IsDefined()) {
		try {
			return parent[key].as<T>();
		}
		catch (const YAML::Exception& e) {
			print_error(e.what());
			return defaultValue;
		}
	}
	return defaultValue;
}

// LOADER (public)
// Try to load the world_data file.
bool load_file(const std::string& filepath, YAML::Node& root) {
	try {
		root = YAML::LoadFile(filepath);
	}
	catch (const YAML::Exception& e) {
		print_error(e.what());
		return false;
	}
	return true;
}

// --- PARSER (public) ---
// Validate each data and construct the global world structure.
bool parse_file(const YAML::Node& root, WorldConfig& world) {
	try {
		// Check LOCATIONS
		if (root["world"] && root["world"]["locations"] && root["world"]["locations"].IsMap()) {
			for (const auto& entry : root["world"]["locations"]) {
				std::string loc_id = entry.first.as<std::string>();
				world.locations[loc_id] = parse_locationConfig(loc_id, entry.second);
			}
		}

		// Check ITEMS
		if (root["items"] && root["items"].IsMap()) {
			for (const auto& entry : root["items"]) {
				std::string item_id = entry.first.as<std::string>();
				world.items[item_id] = parse_itemConfig(item_id, entry.second);
			}
		}

		// Check ENTITIES
		if (root["entities"] && root["entities"].IsMap()) {
			for (const auto& entry : root["entities"]) {
				std::string entity_id = entry.first.as<std::string>();
				world.entities[entity_id] = parse_entityConfig(entity_id, entry.second);
			}
		}
	}
	catch (const std::exception& e) {
		print_error(std::string("PARSING FAILED!\n") + e.what());
		return false;
	}

	return true;
}

// Parsing for the locations part.
LocationConfig parse_locationConfig(const std::string& loc_id, const YAML::Node& node) {
	LocationConfig config;

	config.name = getValue<std::string>(node, "name", "");
	config.description = getValue<std::string>(node, "description", "");
	check_global_data_validation(config.name, config.description, loc_id);

	if (node["exits"] && node["exits"].IsMap()) {
		for (const auto& entry : node["exits"]) {
			Direction dir = convert_direction(entry.first.as<std::string>());
			config.exits[dir] = entry.second.as<std::string>();
		}
	}
	config.spawns = getValue<std::vector<std::string>>(node, "spawns", {});
	config.items = getValue<std::vector<std::string>>(node, "items", {});
	return config;
}

// Parsing for the items part.
ItemConfig parse_itemConfig(const std::string& item_id, const YAML::Node& node) {
	ItemConfig config;

	config.name = getValue<std::string>(node, "name", "");
	config.description = getValue<std::string>(node, "description", "");
	check_global_data_validation(config.name, config.description, item_id);

	config.type = convert_itemType(getValue<std::string>(node, "type", ""));
	if (config.type == ItemType::UNKNOWN) {
		throw std::runtime_error(item_id + " missing type for this item. Use: WEAPON, KEY or CONSUMABLE.");
	}
	config.damage = getValue<int>(node, "damage", 0);
	check_int(config.damage, item_id);
	config.hp = getValue<int>(node, "hp", 0);
	check_int(config.hp, item_id);
	return config;
}

// Parsing for the entities part.
EntityConfig parse_entityConfig(const std::string& entity_id, const YAML::Node& node) {
	EntityConfig config;

	config.name = getValue<std::string>(node, "name", "");
	config.description = getValue<std::string>(node, "description", "");
	check_global_data_validation(config.name, config.description, entity_id);

	if (node["dialogue"] && node["dialogue"].IsMap()) {
		for (const auto& entry : node["dialogue"]) {
			std::string dial_key = entry.first.as<std::string>();
			config.dialogue[dial_key] = entry.second.as<std::string>();
		}
	}
	config.type = convert_enemyType(getValue<std::string>(node, "type", ""));
	if (config.type == EnemyType::UNKNOWN) {
		throw std::runtime_error(entity_id + " missing type for this item. Use: ENEMY, BOSS, NPC or SHOP.");
	}
	config.hp = getValue<int>(node, "hp", 100);
	check_int(config.hp, entity_id);
	return config;
}

// --- CONVERTER ---
// Convert the direction in string to an enum.
Direction convert_direction(const std::string& direction_str) {
	if (direction_str == "north") return Direction::NORTH;
	if (direction_str == "south") return Direction::SOUTH;
	if (direction_str == "east")  return Direction::EAST;
	if (direction_str == "west")  return Direction::WEST;

	return Direction::UNKNOWN;
}

// Convert the item type in string to an enum.
ItemType convert_itemType(const std::string& itemtype_str) {
	if (itemtype_str == "weapon") return ItemType::WEAPON;
	if (itemtype_str == "key") return ItemType::KEY;
	if (itemtype_str == "consumable")  return ItemType::CONSUMABLE;

	return ItemType::UNKNOWN;
}

// Convert the enemy type in string to an enum.
EnemyType convert_enemyType(const std::string& enemytype_str) {
	if (enemytype_str == "enemy") return EnemyType::ENEMY;
	if (enemytype_str == "boss") return EnemyType::BOSS;
	if (enemytype_str == "npc")  return EnemyType::NPC;
	if (enemytype_str == "shop")  return EnemyType::SHOP;

	return EnemyType::UNKNOWN;
}

// --- ERROR ---

// Checker for the name and description.
void check_global_data_validation(const std::string& name, const std::string& desc, const std::string& id) {
	if (name.empty()) {
		throw std::runtime_error(id + " name can't be empty.");
	}
	if (desc.empty()) {
		throw std::runtime_error(id + " description can't be empty.");
	}
}

// Check if int is positive.
void check_int(int value, const std::string& id) {
	if (0 > value) {
		throw std::runtime_error(id + " invalid integer. Need to be positive.");
	}
}
