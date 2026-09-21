/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:05:44 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/21 10:34:58 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <filesystem>
# include <map>
# include <utility>
# include "Entity.hpp"
# include "base_class/items/Item.hpp"

namespace fs = std::filesystem;

class Player : public Entity {
	private:
	std::map<ItemID, std::unique_ptr<Item>> _inventory;

	public:
		Player(const std::string& name, const fs::path& sprite, int health) :
			Entity(name,sprite, health) {}

		// Inventory
		Item* addItemToInventory(std::unique_ptr<Item> item);
		bool removeItemFromInventory(ItemID id);
		bool checkItemInInventory(ItemID id) const;
		Item* getItem(ItemID id) const;
		ItemID getItemIdByName(const std::string& name) const;
		std::string getItemInInventory() const;
};

// Inventory System
Item* Player::addItemToInventory(std::unique_ptr<Item> item) {
	if (!item) {
		sendObjectError("Can't add item: null pointer provided.");
		return nullptr;
	}

	std::string item_name = item->getName();
	if (item_name.empty()) {
		sendObjectError("Can't add item because name is empty.");
		return nullptr;
	}

	ItemID id = item->getId();
	Item* item_ptr = item.get();
	_inventory[id] = std::move(item);
	return item_ptr;
}

bool Player::removeItemFromInventory(ItemID id) {
	if (_inventory.erase(id) > 0) {
        return true;
    }
	sendObjectError("Can't remove item: ID " + std::to_string(id) + " not in player inventory.");
    return false;
}

bool Player::checkItemInInventory(ItemID id) const {
	if (_inventory.count(id)) {
		return true;
	}
	return false;
}

Item* Player::getItem(ItemID id) const {
    auto it = _inventory.find(id);
    if (it != _inventory.end()) {
        return it->second.get();
    }
    return nullptr;
}

ItemID Player::getItemIdByName(const std::string& name) const {
	for (const auto& entry : _inventory) {
		if (entry.second->getName() == name) {
			return entry.first;
		}
	}
	return 0;
}

std::string Player::getItemInInventory() const {
	if (_inventory.size() == 0) {
		return ("No item in inventory.\n");
	}

	std::string inventory = "Item in " + this->getName() + ":\n";
	for (const auto& entry : _inventory) {
		inventory += entry.second->getName() + "\n";
	}
	return (inventory);
}
