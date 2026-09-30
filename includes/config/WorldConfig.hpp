/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WorldConfig.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 23:17:02 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/30 23:41:12 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include <unordered_map>
# include <vector>

enum Direction {NORTH, SOUTH, EAST, WEST};
enum ItemType {WEAPON, KEY, CONSUMABLE};
enum EnemyType {ENEMY, BOSS, NPC, SHOP};

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
	std::unordered_map<std::string, int> stats;
};
