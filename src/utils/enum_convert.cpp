/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum_convert.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 16:48:05 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/21 14:17:58 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "config/Enums.hpp"


// *Return a direction enum in string format.*
std::string direction_to_string(Direction dir) {
	switch (dir) {
		case Direction::NORTH:	return "north";
		case Direction::SOUTH:	return "south";
		case Direction::EAST: 	return "east";
		case Direction::WEST: 	return "west";
		default:				return "unknown";
	}
}

// *Return a enemy type enum in string format.*
std::string enemy_type_to_string(EnemyType type) {
	switch (type) {
		case EnemyType::NPC:	return "npc";
		case EnemyType::ENEMY:	return "enemy";
		case EnemyType::SHOP:	return "shop";
		case EnemyType::BOSS:	return "boss";
		default:				return "unknown";
	}
}

// *Return a item type enum in string format.*
std::string item_type_to_string(ItemType type) {
	switch (type) {
		case ItemType::CONSUMABLE:	return "consumable";
		case ItemType::KEY:			return "key";
		case ItemType::WEAPON:		return "weapon";
		default:					return "unknown";
	}
}

// *Return a quest statut enum in string format.*
std::string quest_state_to_string(QuestState state) {
	switch (state) {
		case QuestState::COMPLETED:		return "completed";
		case QuestState::IN_PROGRESS:	return "active";
		case QuestState::NOT_FOUND:		return "not found";
		default:						return "unknown";
	}
}


// *Return a string in Direction enum if exist.*
Direction direction_str_to_enum(const std::string& direction_str) {
	// Capitalize the command
	std::string dir = direction_str;
	for (char& c : dir) {
		c = std::toupper(static_cast<unsigned char>(c));
	}

	if (dir == "NORTH") {
		return Direction::NORTH;
	}
	else if (dir == "SOUTH") {
		return Direction::SOUTH;
	}
	else if (dir == "EAST") {
		return Direction::EAST;
	}
	else if (dir == "WEST") {
		return Direction::WEST;
	}
	else {
		return Direction::UNKNOWN;
	}
}
