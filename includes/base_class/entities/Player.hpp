/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:05:44 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 11:51:23 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <filesystem>
# include <map>
# include <utility>
# include "Entity.hpp"
# include "base_class/items/Item.hpp"

namespace fs = std::filesystem;

class Player : public Entity {
	private :
		std::map<ItemID, std::unique_ptr<Item>> _inventory;

	public :
		Player(
			const std::string& name, const std::string& description, const fs::path& sprite,
			EnemyType type, int health);

		// Inventory
		Item* addItemToInventory(std::unique_ptr<Item> item);
		bool removeItemFromInventory(ItemID id);
		bool checkItemInInventory(ItemID id) const;
		Item* getItem(ItemID id) const;
		ItemID getItemIdByName(const std::string& name) const;
		std::string getItemInInventory() const;
};

