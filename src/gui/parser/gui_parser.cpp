/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_parser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 08:21:07 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 09:56:21 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <filesystem>

# include "gui.h"
# include "parser.h"
# include "utils.h"

namespace fs = std::filesystem;

enum class DataType {LOCATION, ENTITY, SPRITE, MUSIC, SOUND};

LocationConfig parse_locationConfig(const std::string& loc_id, const YAML::Node& node);
EntityConfig parse_entityConfig(const std::string& entity_id, const YAML::Node& node);
SpriteConfig parse_spriteConfig(const std::string& sprite_id, const YAML::Node& node);
SoundConfig parse_soundConfig(const std::string& sound_id, const YAML::Node& node);
MusicConfig parse_musicConfig(const std::string& music_id, const YAML::Node& node);
void check_resource(const std::string& sprite, const std::string& id, DataType type);
std::string data_type_to_string(DataType type);

// --- PARSER (public) ---
// Validate data for the gui and valid the world structure.
bool parse_file_for_gui(std::queue<YAML::Node>& nodes_list, WorldConfig& world) {
	YAML::Node root = pop_front(nodes_list);
	YAML::Node root_sounds = pop_front(nodes_list);
	YAML::Node root_sprites = pop_front(nodes_list);

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

		// Check SPRITES
		if (root_sprites["sprites"] && root_sprites["sprites"].IsMap()) {
			for (const auto& entry : root_sprites["sprites"]) {
				std::string sprite_id = entry.first.as<std::string>();
				world.sprite[sprite_id] = parse_spriteConfig(sprite_id, entry.second);
			}
		}

		// Check SOUNDS
		if (root_sounds["sounds"] && root_sounds["sounds"].IsMap()) {
			for (const auto& entry : root_sounds["sounds"]) {
				std::string sound_id = entry.first.as<std::string>();
				world.sound[sound_id] = parse_soundConfig(sound_id, entry.second);
			}
		}

		// Check MUSICS
		if (root_sounds["musics"] && root_sounds["musics"].IsMap()) {
			for (const auto& entry : root_sounds["musics"]) {
				std::string music_id = entry.first.as<std::string>();
				world.music[music_id] = parse_musicConfig(music_id, entry.second);
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
	check_resource(config.tile_map, loc_id, DataType::LOCATION);

	return config;
}

// Parsing for the entities part.
EntityConfig parse_entityConfig(const std::string& entity_id, const YAML::Node& node) {
	EntityConfig config;

	config.sprite = getValue<std::string>(node, "sprite", "");
	check_resource(config.sprite, entity_id,  DataType::ENTITY);

	return config;
}

// Parsing for the sprites part.
SpriteConfig parse_spriteConfig(const std::string& sprite_id, const YAML::Node& node) {
	SpriteConfig config;

	config.name = getValue<std::string>(node, "name", "");
	config.path = getValue<std::string>(node, "path", "");
	check_resource(config.path, sprite_id, DataType::SPRITE);

	return config;
}

// Parsing for the sounds part.
SoundConfig parse_soundConfig(const std::string& sound_id, const YAML::Node& node) {
	SoundConfig config;

	config.name = getValue<std::string>(node, "name", "");
	config.path = getValue<std::string>(node, "path", "");
	check_resource(config.path, sound_id, DataType::SOUND);

	return config;
}

// Parsing for the music part.
MusicConfig parse_musicConfig(const std::string& music_id, const YAML::Node& node) {
	MusicConfig config;

	config.name = getValue<std::string>(node, "name", "");
	config.path = getValue<std::string>(node, "path", "");
	check_resource(config.path, music_id, DataType::MUSIC);

	return config;
}

// --- CHECKER ---
// Check if sprite exist and extension (.png)
void check_resource(const std::string& sprite, const std::string& id, DataType type) {
	if (sprite.empty()) {
		if (type == DataType::SOUND) {
			throw std::runtime_error(id + " missing sound.\n");
		}
		else if (type == DataType::MUSIC) {
			throw std::runtime_error(id + " missing music.\n");
		}
		else {
			throw std::runtime_error(id + " missing sprite for this " + data_type_to_string(type) + ".\n");
		}
	}

	fs::path p(sprite);
	// Check that file exist
	std::error_code ec;
	if (!fs::exists(p, ec) || ec) {
		if (type == DataType::SOUND) {
			throw std::runtime_error("'" + id + "'" + " missing sound.");
		}
		else if (type == DataType::MUSIC) {
			throw std::runtime_error("'" + id + "'" + " missing music.");
		}
		throw std::runtime_error("'" + id + "'" + " missing sprite.");
	}

	// Check extension
	if (type == DataType::SOUND) {
		if (p.extension() != ".ogg" && p.extension() != ".wav") {
			throw std::runtime_error("'" + id + "'" + + " sound must be in wav or ogg.");
		}
	}
	else if (type == DataType::MUSIC) {
		if (p.extension() != ".ogg") {
			throw std::runtime_error("'" + id + "'" + + " music must be in ogg.");
		}
	}
	else {
		if (p.extension() != ".png") {
			throw std::runtime_error("'" + id + "'" + + " sprite must be in png.");
		}
	}
}

// --- UTILS ---
// Convert enum data type to string
std::string data_type_to_string(DataType type) {
    switch (type) {
        case DataType::LOCATION: return "location";
        case DataType::ENTITY:   return "entity";
        case DataType::SPRITE:   return "sprite";
        case DataType::MUSIC:    return "music";
        case DataType::SOUND:    return "sound";
        default:                 return "unknown";
    }
}
