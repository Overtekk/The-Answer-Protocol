/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_structure.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 16:36:01 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/02 17:46:02 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include "utils.h"

void debug_print_structure(WorldConfig& world) {
	for (const auto& [loc_id, loc] : world.locations) {
		std::cout << "[" + loc_id + "]" + "{'" + loc.name + "', '" + loc.description + "', ";
		if (loc.special) {
			std::cout << "special: true, ";
		}
		std::cout << "exits: [";
		for (const auto& [dir, location] : loc.exits) {
			std::cout << "'" + direction_to_string(dir) + "': '" + location + "', ";
		}
		std::cout << "], spawns: [";
		for (const auto& entity : loc.spawns) {
			std::cout << "'" + entity + "', ";
		}
		std::cout << "], items: [";
		for (const auto& item : loc.items) {
			std::cout << "'" + item + "', ";
		}
		std::cout << "]}\n";
	}
	std::cout << "\n";

	for (const auto& [item_id, item] : world.items) {
		std::cout << "[" + item_id + "]" + "{'" + item.name + "', '" + item.description + "', ";
		std::cout << "type: " + item_type_to_string(item.type);
		if (item.damage > 0) {
			std::cout << ", damage: " + std::to_string(item.damage);
		}
		if (item.hp > 0) {
			std::cout << ", hp: " + std::to_string(item.hp);
		}
		std::cout << "}\n";
	}
	std::cout << "\n";

	for (const auto& [entity_id, entity] : world.entities) {
		std::cout << "[" + entity_id + "]" + "{'" + entity.name + "', '" + entity.description + "', ";
		std::cout << "sprite: '" + entity.sprite + "', ";
		std::cout << "type: " + enemy_type_to_string(entity.type);
		std::cout << ", hp: " + std::to_string(entity.hp);
		std::cout << ", dialogue[" ;
		for (const auto& [dialogue_id, dialogue] : entity.dialogue) {
			std::cout << dialogue_id + "('" + dialogue + "'), ";
		}
		std::cout << "}\n";
	}
	std::cout << "\n";
}
