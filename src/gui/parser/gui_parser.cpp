/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 08:21:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 10:11:18 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <filesystem>
# include "gui.h"
# include "utils.h"

namespace fs = std::filesystem;

LocationConfig parse_locationConfig(const std::string& loc_id, const YAML::Node& node);
EntityConfig parse_entityConfig(const std::string& entity_id, const YAML::Node& node);
void check_sprite(const std::string& sprite, const std::string& id);

// --- PARSER (public) ---
// Validate data for the gui and valid the world structure.
bool parse_file_for_gui(const YAML::Node& root, WorldConfig& world) {
	try {
		// Check LOCATIONS
		if (root["world"] && root["world"]["locations"] && root["world"]["locations"].IsMap()) {
			for (const auto& entry : root["world"]["locations"]) {
				std::string loc_id = entry.first.as<std::string>();
				world.locations[loc_id] = parse_locationConfig(loc_id, entry.second);
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

	print_success("World Data (gui) loaded!");

	return true;
}

// --- PARSER ---
// Parsing for the locations part.
LocationConfig parse_locationConfig(const std::string& loc_id, const YAML::Node& node) {
	LocationConfig config;

	config.tile_map = getValue<std::string>(node, "tile_map", "");
	check_sprite(config.tile_map, loc_id);

	return config;
}

// Parsing for the entities part.
EntityConfig parse_entityConfig(const std::string& entity_id, const YAML::Node& node) {
	EntityConfig config;

	config.sprite = getValue<std::string>(node, "sprite", "");
	check_sprite(config.sprite, entity_id);

	return config;
}

// --- CHECKER ---
// Check if sprite exist and extension (.png)
void check_sprite(const std::string& sprite, const std::string& id) {
	if (sprite.empty()) {
		throw std::runtime_error(id + " missing sprite for this entity.");
	}

	fs::path p(sprite);
	// Check that file exist
	std::error_code ec;
	if (!fs::exists(p, ec) || ec) {
		throw std::runtime_error("'" + id + "'" + " missing sprite.");
	}
	// Check extension
	if (p.extension() != ".png") {
		throw std::runtime_error("'" + id + "'" + + " sprite must be in png.");
	}
}
