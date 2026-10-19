/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:05:44 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/19 16:01:00 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <map>
# include <memory>
# include <optional>
# include <unordered_map>

# include "Entity.hpp"
# include "base_class/items/Item.hpp"

// PlayerID for the session
using PlayerID = uint64_t;


// * Represent a player *
class Player : public Entity {
	private :
		std::map<ItemID, Item*>	_inventory;

		// Information
		std::string	_zone;

		inline static	PlayerID _id = 1;

	public :
		// --- CONSTRUCTOR ---
		Player(const std::string& name);
		// --- DESTRUCTOR ---
        ~Player() override = default;

		// --- GETTER ---
		const std::string&	getZone() const;

		// --- SETTER ---
		void	setZone(const std::string& new_zone);

		// --- INVENTORY SYSTEM ---
		Item* 			addItemToInventory(Item* item);
		Item* 			popItemFromInventory(ItemID id);
		bool			removeItemFromInventory(ItemID id);
		const Item*		getItem(ItemID id) const;
		Item* 			getItem(ItemID id);
		std::optional<ItemID>	getItemIdByName(const std::string& name) const;

		bool 			checkItemInInventory(ItemID id) const;
		std::string		getItemInInventory(bool add_details) const;
};
