/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WorldConfig.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 23:17:02 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/22 18:18:22 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <string>
# include <unordered_map>
# include <vector>

# include "Enums.hpp"


/// ** Structures that hold raws data for the manager to create the objects later on. **
// Contains the data of a zone.
struct LocationConfig {
	std::string name;
	std::string description;
	std::string tile_map;
	std::unordered_map<Direction, std::string> exits;
	std::vector<std::string> spawns;
	std::vector<std::string> items;
	bool special;
};

// Contains the data of an item.
struct ItemConfig {
	std::string name;
	std::string description;
	ItemType type;
	int damage;
	int hp;
};

// Contains the data of an entity.
struct EntityConfig {
	std::string name;
	std::string description;
	std::string sprite;
	std::unordered_map<std::string, std::string> dialogue;
	EnemyType type;
	int hp;
};

// Contains the data of a quest.
struct QuestConfig {
	std::string name;
	std::string description;
	bool spawn_with_quest;
};

// Contains the data of a sprite (other than entity and tilesmap).
struct SpriteConfig {
	std::string name;
	std::string path;
};

// Contains the data of a sound/sfx.
struct SoundConfig {
	std::string name;
	std::string path;
};

// Contains the data of a music.
struct MusicConfig {
	std::string name;
	std::string path;
};

// Structure that hold every struct above to have a global structure.
struct WorldConfig {
	std::unordered_map<std::string, LocationConfig> locations;
	std::unordered_map<std::string, ItemConfig> items;
    std::unordered_map<std::string, EntityConfig> entities;
	std::unordered_map<std::string, QuestConfig> quests;
	std::unordered_map<std::string, SpriteConfig> sprite;
	std::unordered_map<std::string, SoundConfig> sound;
	std::unordered_map<std::string, MusicConfig> music;
};
