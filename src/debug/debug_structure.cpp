/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_structure.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/02 16:36:01 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/05 12:02:10 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include "utils.h"

void debug_print_structure(WorldConfig& world, bool show_gui_info = false) {
	std::cout << "LOCATIONS:\n";
	for (const auto& [loc_id, loc] : world.locations) {
		std::cout << "[" + loc_id + "]" + "{'" + loc.name + "', '" + loc.description + "', ";
		if (show_gui_info) {
			std::cout << "tile_map: '" + loc.tile_map + "', ";
		}
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

	std::cout << "ITEMS:\n";
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

	std::cout << "ENTITIES:\n";
	for (const auto& [entity_id, entity] : world.entities) {
		std::cout << "[" + entity_id + "]" + "{'" + entity.name + "', '" + entity.description + "', ";
		if (show_gui_info) {
			std::cout << "sprite: '" + entity.sprite + "', ";
		}
		std::cout << "type: " + enemy_type_to_string(entity.type);
		std::cout << ", hp: " + std::to_string(entity.hp);
		std::cout << ", dialogue[" ;
		for (const auto& [dialogue_id, dialogue] : entity.dialogue) {
			std::cout << dialogue_id + "('" + dialogue + "'), ";
		}
		std::cout << "}\n";
	}
	std::cout << "\n";

	std::cout << "SPRITES:\n";
	for (const auto& [sprite_id, sprite] : world.sprite) {
		std::cout << "[" + sprite_id + "]" + "{'" + sprite.name + "', '" + sprite.path + "'}\n";
	}
	std::cout << "\n";

	std::cout << "SOUNDS:\n";
	for (const auto& [sound_id, sound] : world.sound) {
		std::cout << "[" + sound_id + "]" + "{'" + sound.name + "', '" + sound.path + "'}\n";
	}
	std::cout << "\n";

	std::cout << "MUSICS:\n";
	for (const auto& [music_id, music] : world.music) {
		std::cout << "[" + music_id + "]" + "{'" + music.name + "', '" + music.path + "'}\n";
	}
	std::cout << "\n";
}
