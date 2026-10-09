/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Room.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 11:59:17 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/09 14:58:44 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <string>
# include <filesystem>
# include <unordered_map>

# include <nlohmann/json.hpp>
# include "base_class/items/Item.hpp"
# include "base_class/entities/Player.hpp"
# include "base_class/entities/Entity.hpp"
# include "config/Enums.hpp"

namespace fs = std::filesystem;


// * ABSTRACT CLASS *
class Room {
	private :
		std::string									_id;
		std::string									_name;
		std::string									_description;
		fs::path									_background;
		std::unordered_map<ItemID, Item*>			_items;
		std::unordered_map<std::string, Player*>	_players;
		std::unordered_map<std::string, Entity*>	_entity;
		std::unordered_map<Direction, Room*>		_exits;
		bool										_special;

	public:
		// --- CONSTRUCTOR ---
		Room(
			const std::string& id, const std::string& name, const std::string& description,
			const fs::path& background, const bool _special);
		// --- DESTRUCTOR ---
		~Room() = default;

		// Data
		nlohmann::json	getRoomData();

		// ID
		const std::string&	getID() const;

		// Name
		std::string		getName() const;
		bool			setName(const std::string& new_name);

		// Description
		std::string		getDescription() const;
		bool			setDescription(const std::string& new_desc);

		// Players
		bool			addPlayer(Player* player);
		Player*			popPlayer(const std::string& name);
		Player*			getPlayer(const std::string& name);

		// Entity
		bool			addEntity(Entity* entity);
		Entity*			popEntity(const std::string& name);
		Entity*			getEntity(const std::string& name);

		// Items
		bool			placeItem(Item* item);
		Item*			popItem(ItemID item_id);
		Item*			getItem(ItemID item_id);

		// Directions
		void			setExitNorth(Room* room);
		void			setExitSouth(Room* room);
		void			setExitEast(Room* room);
		void			setExitWest(Room* room);
		void			setExitUnknown(Room* room);
		Room*			getFromDirection(Direction direction);

		// Special stats
		bool			isSpecial() const;

		// Texture
		fs::path		getBGTexturePath() const;

		// Error
		void			sendObjectError(const std::string& error) const;
};
