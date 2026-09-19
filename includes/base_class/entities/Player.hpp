/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 16:05:44 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/19 11:50:23 by roandrie         ###   ########.fr       */
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
	std::map<std::string, std::unique_ptr<Item>> _inventory;

	public:
		Player(const std::string& name, const fs::path& sprite, int health) :
			Entity(name,sprite, health) {}

		bool addItemToInventory(std::unique_ptr<Item>);
		bool removeItemToInventory(const std::string& item_name);
		bool checkItemInInventory(std::string const& item_name);
		std::string getItemInInventory() const;
};

// Inventory System
bool Player::addItemToInventory(std::unique_ptr<Item> item) {
	if (!item) {
		sendObjectError("Can't add item: null pointer provided.");
		return false;
	}

	std::string item_name = item->getName();
	if (item_name.empty()) {
		sendObjectError("Can't add item because name is empty.");
		return false;
	}

	if (checkItemInInventory(item_name)) {
		sendObjectError(item->getName() + " already is player inventory.");
		return false;
	}

	_inventory[item_name] = std::move(item);
	return true;
}

bool Player::removeItemToInventory(const std::string& item_name) {
	if (_inventory.erase(item_name) > 0) {
        return true;
    }
	sendObjectError(item_name + " not in player inventory. Can't remove it.");
	return false;
}

bool Player::checkItemInInventory(std::string const& item_name) {
	if (_inventory.count(item_name)) {
		return true;
	}
	return false;
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
