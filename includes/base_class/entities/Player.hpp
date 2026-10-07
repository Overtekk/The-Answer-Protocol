/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:05:44 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/07 09:59:55 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <filesystem>
# include <map>
# include <utility>
# include "Entity.hpp"
# include "base_class/items/Item.hpp"

namespace fs = std::filesystem;

// * Represent a player *
class Player : public Entity {
	private :
		std::map<ItemID, std::unique_ptr<Item>> _inventory;

	public :
		// --- CONSTRUCTOR ---
		Player(
			const std::string& name, int health);
		// --- DESTRUCTOR ---
        ~Player() = default;

		// --- SETTER ---
		bool setName(std::string& new_name);

		// --- INVENTORY SYSTEM ---
		Item* 		addItemToInventory(std::unique_ptr<Item> item);
		bool 		removeItemFromInventory(ItemID id);
		bool 		checkItemInInventory(ItemID id) const;
		Item* 		getItem(ItemID id) const;
		ItemID 		getItemIdByName(const std::string& name) const;
		std::string getItemInInventory() const;
};
