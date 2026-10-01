/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WorldConfig.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 23:17:02 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/01 16:03:50 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include <unordered_map>
# include <vector>

enum class Direction {NORTH, SOUTH, EAST, WEST, UNKNOWN};
enum class ItemType {WEAPON, KEY, CONSUMABLE, UNKNOWN};
enum class EnemyType {ENEMY, BOSS, NPC, SHOP, UNKNOWN};

struct LocationConfig {
	std::string name;
	std::string description;
	std::unordered_map<Direction, std::string> exits;
	std::vector<std::string> spawns;
	std::vector<std::string> items;
	bool has_save_point;
	bool special;
};

struct ItemConfig {
	std::string name;
	std::string description;
	ItemType type;
	int damage;
	int hp;
};

struct EntityConfig {
	std::string name;
	std::string description;
	std::unordered_map<std::string, std::string> dialogue;
	EnemyType type;
	int hp;
};

struct WorldConfig {
	std::unordered_map<std::string, LocationConfig> locations;
	std::unordered_map<std::string, ItemConfig> items;
    std::unordered_map<std::string, EntityConfig> entities;
};
