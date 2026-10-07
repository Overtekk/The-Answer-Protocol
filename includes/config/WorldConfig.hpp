/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WorldConfig.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 23:17:02 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 10:31:07 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include <unordered_map>
# include <vector>
# include "config/Enums.hpp"

/// ** Structures that hold raws data for the manager to create the objects later on. **
// Contains the data for the locations.
struct LocationConfig {
	std::string name;
	std::string description;
	std::string tile_map;
	std::unordered_map<Direction, std::string> exits;
	std::vector<std::string> spawns;
	std::vector<std::string> items;
	bool special;
};

// Contains the data for the items.
struct ItemConfig {
	std::string name;
	std::string description;
	ItemType type;
	int damage;
	int hp;
};

// Contains the data for the entities.
struct EntityConfig {
	std::string name;
	std::string description;
	std::string sprite;
	std::unordered_map<std::string, std::string> dialogue;
	EnemyType type;
	int hp;
};

// Contains the data for the sprites (other than entities and tilesmap).
struct SpriteConfig {
	std::string name;
	std::string path;
};

// Contains the data for the sounds/sfx.
struct SoundConfig {
	std::string name;
	std::string path;
};

// Contains the data for the musics.
struct MusicConfig {
	std::string name;
	std::string path;
};

// Structure that hold every struct above to have a global structure.
struct WorldConfig {
	std::unordered_map<std::string, LocationConfig> locations;
	std::unordered_map<std::string, ItemConfig> items;
    std::unordered_map<std::string, EntityConfig> entities;
	std::unordered_map<std::string, SpriteConfig> sprite;
	std::unordered_map<std::string, SoundConfig> sound;
	std::unordered_map<std::string, MusicConfig> music;
};
