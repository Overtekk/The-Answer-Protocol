/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:05:44 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 11:09:08 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <map>
# include <memory>
# include <uuid/uuid.h>

# include "Entity.hpp"
# include "base_class/items/Item.hpp"

// PlayerID for the session
using PlayerID = uint64_t;


// * Represent a player *
class Player : public Entity {
	private :
		std::map<ItemID, std::unique_ptr<Item>>	_inventory;

		// Information
		std::string	_zone;

		inline static	PlayerID _next_id = 1;

	public :
		// --- CONSTRUCTOR ---
		Player(const std::string& name);
		// --- DESTRUCTOR ---
        ~Player() = default;

		// --- GETTER ---
		const std::string&	getZone() const;

		// --- SETTER ---
		void	setZone(const std::string& new_zone);

		// --- INVENTORY SYSTEM ---
		Item* 			addItemToInventory(std::unique_ptr<Item> item);
		bool 			removeItemFromInventory(ItemID id);
		bool 			checkItemInInventory(ItemID id) const;
		Item* 			getItem(ItemID id) const;
		ItemID 			getItemIdByName(const std::string& name) const;
		std::string		getItemInInventory() const;

		// --- UUID ---
		std::string	generate_uuid_v4() const;
};
