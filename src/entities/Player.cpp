/* *********************************************************************** */
/*                                                                         */
/*                                                     :::      ::::::::   */
/* Player.cpp                                        :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+     */
/* By: roandrie <roandrie@student.42lehavre.fr   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+           */
/* Created: 2026/09/21 14:06:43 by roandrie        #+#    #+#              */
/* Updated: 2026/10/07 10:23:29 by roandrie        ###   ########.fr       */
/*                                                                         */
/* *********************************************************************** */

# include "base_class/entities/Player.hpp"

// --- CONSTRUCTOR ---
Player::Player(const std::string& name):
	Entity(name, "", EnemyType::UNKNOWN, 100) {}

// --- SETTER ---
bool	Player::setName(std::string& new_name) {
	if (new_name.length() >= 3 && new_name.length() <= 20) {
		_name = new_name;
		return true;
	}
	sendObjectError("Can't modify name. Minimum 3 and maximum 20 characters.");
	return false;
}

// --- INVENTORY SYSTEM ---
// * Add an item to the player inventory. *
Item*	Player::addItemToInventory(std::unique_ptr<Item> item) {
	if (!item) {
		sendObjectError("Can't add item: null pointer provided.");
		return nullptr;
	}

	std::string item_name = item->getName();
	if (item_name.empty()) {
		sendObjectError("Can't add item because name is empty.");
		return nullptr;
	}

	ItemID id = item->getID();
	Item* item_ptr = item.get();
	_inventory[id] = std::move(item);
	return item_ptr;
}

// * Remove an item from the player inventory. *
bool	Player::removeItemFromInventory(ItemID id) {
	if (_inventory.erase(id) > 0) {
        return true;
    }
	sendObjectError("Can't remove item: ID " + std::to_string(id) + " not in player inventory.");
    return false;
}

// * Check for an item in the player inventory. *
bool	Player::checkItemInInventory(ItemID id) const {
	if (_inventory.count(id)) {
		return true;
	}
	return false;
}

// * Get the item by ID from the player inventory. *
Item*	Player::getItem(ItemID id) const {
    auto it = _inventory.find(id);
    if (it != _inventory.end()) {
        return it->second.get();
    }
    return nullptr;
}

// * Get the ID of an item by its name. *
ItemID	Player::getItemIdByName(const std::string& name) const {
	for (const auto& entry : _inventory) {
		if (entry.second->getName() == name) {
			return entry.first;
		}
	}
	return 0;
}

// * Get the inventory of the player. *
std::string	Player::getItemInInventory() const {
	if (_inventory.size() == 0) {
		return ("No item in inventory.\n");
	}

	std::string inventory = "Item in " + this->getName() + ":\n";
	for (const auto& entry : _inventory) {
		inventory += entry.second->getName() + "\n";
	}
	return (inventory);
}

// --- UUID SYSTEM ---
// * Generate an unique UUID. *
std::string	Player::generate_uuid_v4() const {
	uuid_t	uuid;
	uuid_generate_random(uuid);

	char str_uuid[37]; // 36 characters + '\0'
	uuid_unparse_lower(uuid, str_uuid);

	return std::string(str_uuid);
}
