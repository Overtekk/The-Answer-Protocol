/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 23:35:41 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/01 15:01:09 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <yaml-cpp/yaml.h>
# include "utils.h"
# include "config/WorldConfig.hpp"

Direction convert_direction(const std::string& direction_str);
ItemType convert_itemType(const std::string& itemtype_str);
ItemType convert_itemType(const std::string& itemtype_str);
ItemConfig parse_itemConfig(const YAML::Node& node);


// TEMPLATE
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

// LOADER
// public
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

// PARSER
// public
bool parse_file(const YAML::Node& root, WorldConfig& world) {
	// Check ITEMS
	if (root["items"] && root["items"].IsMap()) {
		for (const auto& entry : root["items"]) {
			std::string item_id = entry.first.as<std::string>();
			world.items[item_id] = parse_itemConfig(entry.second);
		}
	}
	return true;
}

LocationConfig parse_locationConfig(const YAML::Node& node) {
	LocationConfig config;

	config.name = getValue<std::string>(node, "name", "");
	config.description = getValue<std::string>(node, "description", "");
	if (node["exits"] && node["exists"].IsMap()) {
		for (const auto& entry : node["exits"]) {
			Direction dir = convert_direction(getValue<Direction>(entry.first.as<std::string>(), "type", ""));
			std::string room_id = entry.second.as<std::string>();
			config.exits[dir] = room_id;
		}
	}
	config
}

ItemConfig parse_itemConfig(const YAML::Node& node) {
	ItemConfig config;

	config.name = getValue<std::string>(node, "name", "");
	config.description = getValue<std::string>(node, "description", "");
	config.type = convert_itemType(getValue<std::string>(node, "type", ""));
	config.damage = getValue<int>(node, "damage", 0);
	config.hp = getValue<int>(node, "hp", 0);
	return config;
}

// CONVERTER

Direction convert_direction(const std::string& direction_str) {
	if (direction_str == "north") return NORTH;
	if (direction_str == "south") return SOUTH;
	if (direction_str == "east")  return EAST;
	if (direction_str == "west")  return WEST;

	throw std::runtime_error("Unknown direction: " + direction_str);
}

ItemType convert_itemType(const std::string& itemtype_str) {
	if (itemtype_str == "weapon") return WEAPON;
	if (itemtype_str == "key") return KEY;
	if (itemtype_str == "consumable")  return CONSUMABLE;

	throw std::runtime_error("Unknown item type: " + itemtype_str);
}

EnemyType convert_enemyType(const std::string& enemytype_str) {
	if (enemytype_str == "enemy") return ENEMY;
	if (enemytype_str == "boss") return BOSS;
	if (enemytype_str == "npc")  return NPC;
	if (enemytype_str == "shop")  return SHOP;

	throw std::runtime_error("Unknown enemy type: " + enemytype_str);
}
