/* *********************************************************************** */
/*                                                                         */
/*                                                     :::      ::::::::   */
/* Player.cpp                                        :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+     */
/* By: roandrie <roandrie@student.42lehavre.fr   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+           */
/* Created: 2026/09/21 14:06:43 by roandrie        #+#    #+#              */
/* Updated: 2026/09/21 14:42:55 by roandrie        ###   ########.fr       */
/*                                                                         */
/* *********************************************************************** */

# include "base_class/entities/Player.hpp"

Player::Player(
	const std::string& name, const fs::path& sprite, int health
):
	Entity(name,sprite, health) {}

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
