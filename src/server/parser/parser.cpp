/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 23:35:41 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 09:45:33 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <filesystem>
# include "utils.h"

namespace fs = std::filesystem;

LocationConfig parse_locationConfig(const std::string& loc_id, const YAML::Node& node, std::unordered_set<std::string>& knows_locations);
ItemConfig parse_itemConfig(const std::string& item_id, const YAML::Node& node, std::unordered_set<std::string>& knows_items);
EntityConfig parse_entityConfig(const std::string& entity_id, const YAML::Node& node, std::unordered_set<std::string>& knows_entities);
Direction convert_direction(const std::string& direction_str);
ItemType convert_itemType(const std::string& itemtype_str);
EnemyType convert_enemyType(const std::string& enemytype_str);
void check_global_data_validation(const std::string& name, const std::string& desc, const std::string& id);
void check_int(int value, const std::string& id);
void check_sprite(const std::string&  sprite, const std::string& id);
void check_locations_data(const WorldConfig& world, std::unordered_set<std::string>& knows_locations, std::unordered_set<std::string>& knows_items, std::unordered_set<std::string>& knows_entities);
std::string direction_to_string(Direction dir);

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
	std::unordered_set<std::string> knows_locations; // used to check if a location exist
	std::unordered_set<std::string> knows_items; // used to check if a item exist
	std::unordered_set<std::string> knows_entities; // used to check if a entity exist

	try {
		// Check LOCATIONS
		if (root["world"] && root["world"]["locations"] && root["world"]["locations"].IsMap()) {
			for (const auto& entry : root["world"]["locations"]) {
				std::string loc_id = entry.first.as<std::string>();
				world.locations[loc_id] = parse_locationConfig(loc_id, entry.second, knows_locations);
			}
		}

		// Check ITEMS
		if (root["items"] && root["items"].IsMap()) {
			for (const auto& entry : root["items"]) {
				std::string item_id = entry.first.as<std::string>();
				world.items[item_id] = parse_itemConfig(item_id, entry.second, knows_items);
			}
		}

		// Check ENTITIES
		if (root["entities"] && root["entities"].IsMap()) {
			for (const auto& entry : root["entities"]) {
				std::string entity_id = entry.first.as<std::string>();
				world.entities[entity_id] = parse_entityConfig(entity_id, entry.second, knows_entities);
			}
		}

		// Check if all data are valid
		check_locations_data(world, knows_locations, knows_items, knows_entities);

	}
	catch (const std::exception& e) {
		print_error(std::string("PARSING FAILED!\n") + e.what());
		return false;
	}

	print_success("World Data loaded!");

	return true;
}

// Parsing for the locations part.
LocationConfig parse_locationConfig(
	const std::string& loc_id, const YAML::Node& node, std::unordered_set<std::string>& knows_locations) {
	LocationConfig config;

	knows_locations.insert(loc_id); // added to the set to check later

	// Get name and description and check
	config.name = getValue<std::string>(node, "name", "");
	config.description = getValue<std::string>(node, "description", "");
	check_global_data_validation(config.name, config.description, loc_id);

	// Checks the directions
	if (node["exits"] && node["exits"].IsMap()) {
		for (const auto& entry : node["exits"]) {
			Direction dir = convert_direction(entry.first.as<std::string>());
			config.exits[dir] = entry.second.as<std::string>();
		}
	}

	// Add the spawns and items vector even if they don't exists
	config.spawns = getValue<std::vector<std::string>>(node, "spawns", {});
	config.items = getValue<std::vector<std::string>>(node, "items", {});

	// Add the special bool (default to false)
	config.special = getValue<bool>(node, "special", false);

	return config;
}

// Parsing for the items part.
ItemConfig parse_itemConfig(
	const std::string& item_id, const YAML::Node& node, std::unordered_set<std::string>& knows_items) {
	ItemConfig config;

	knows_items.insert(item_id); // added to the set to check later

	config.name = getValue<std::string>(node, "name", "");
	config.description = getValue<std::string>(node, "description", "");
	check_global_data_validation(config.name, config.description, item_id);

	// Check the type of the item and add it
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
EntityConfig parse_entityConfig(
	const std::string& entity_id, const YAML::Node& node, std::unordered_set<std::string>& knows_entities) {
	EntityConfig config;

	knows_entities.insert(entity_id); // added to the set to check later

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

// --- CHECKER ---
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

void check_locations_data(
	const WorldConfig& world,
	std::unordered_set<std::string>& knows_locations,
	std::unordered_set<std::string>& knows_items,
	std::unordered_set<std::string>& knows_entities) {

	for (const auto& [loc_id, loc] : world.locations) {
		for (const auto& [dir, name] : loc.exits) {

			// Check if a location exist in the directions maps
			if (knows_locations.count(name) == 0) {
				throw std::runtime_error(
					loc_id + ": '" + direction_to_string(dir) + ": " + name + "' is not a valid location.");
			}
			else {
				// Check if a location in a direction as not the same name that the location id
				if (loc_id == name) {
					throw std::runtime_error(
						loc_id + ": '" + direction_to_string(dir) + ": " + name + "' is duplicated. You will broke the reality!");
				}
			}
		}
		for (const auto& entity : loc.spawns) {
			// Check if the entity exist in the list of spawns
			if (knows_entities.count(entity) == 0) {
				throw std::runtime_error(
					loc_id + ": '" + entity + "' is not a valid entity.");
			}
		}
		for (const auto& item : loc.items) {
			// Check if the item exist in the list of items
			if (knows_items.count(item) == 0) {
				throw std::runtime_error(
					loc_id + ": '" + item + "' is not a valid item.");
			}
		}
	}
}

