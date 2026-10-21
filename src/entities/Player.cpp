/* *********************************************************************** */
/*                                                                         */
/*                                                     :::      ::::::::   */
/* Player.cpp                                        :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+     */
/* By: roandrie <roandrie@student.42lehavre.fr   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+           */
/* Created: 2026/09/21 14:06:43 by roandrie        #+#    #+#              */
/* Updated: 2026/10/07 09:36:13 by roandrie        ###   ########.fr       */
/*                                                                         */
/* *********************************************************************** */

# include <string>
# include <utility>

# include "base_class/entities/Player.hpp"
# include "utils.h"
# include "config/Enums.hpp"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
Player::Player(const std::string& name):
	Entity(std::to_string(_id++), name, "", EnemyType::UNKNOWN, 100) {}

// ============================================================================
// ====================       PUBLIC METHODS      =============================
// ============================================================================
// --- GETTER ---
// * Get the current zone of the player. *
const std::string&	Player::getZone() const { return _zone; }

// * Return player not completed quests. *
std::vector<std::string>	Player::getCurrentQuests() const {
	std::vector<std::string>	quests_list;

	for (const auto& quest_id : _quests) {
		if (quest_id.second == QuestState::IN_PROGRESS)
			quests_list.push_back(quest_id.first);
	}
	return quests_list;
}

// * Return player completed quests. *
std::vector<std::string>	Player::getCompletedQuests() const {
	std::vector<std::string>	quests_list;

	for (const auto& quest_id : _quests) {
		if (quest_id.second == QuestState::COMPLETED)
			quests_list.push_back(quest_id.first);
	}
	return quests_list;
}

QuestState	Player::getQuestStatut(const std::string& quest_id) const {
	const auto it = _quests.find(quest_id);
	if (it == _quests.end()) {
		print_log(this->getName() + ": quest \"" + quest_id + "\" not found.");
		return QuestState::NOT_FOUND;
	}
	return it->second;
}

// --- SETTER ---
// * Set the new zone of the player. *
void	Player::setZone(const std::string& new_zone) {
	_zone = new_zone;
}

// * Add a quest to the player. *
void	Player::addQuest(const std::string& quest_id) {
	_quests[quest_id] = QuestState::IN_PROGRESS;
}

// * Remove a quest from the player. *
void	Player::removeQuest(const std::string& quest_id) {
	_quests.erase(quest_id);
}

// * Set a quest as completed. *
void	Player::setQuestCompleted(const std::string& quest_id) {
	_quests[quest_id] = QuestState::COMPLETED;
}

// ============================================================================
// ====================      INVENTORY SYSTEM      ============================
// ============================================================================
// * Add an item to the player inventory. *
Item* Player::addItemToInventory(Item* item) {
	if (!item) {
		sendObjectError("Can't add item: null pointer provided.");
		return nullptr;
	}

	ItemID id = item->getUniqueID();
	_inventory[id] = item;
	return item;
}

// * Pop item from inventory. *
Item* Player::popItemFromInventory(ItemID id) {
	auto it = _inventory.find(id);
	if (it != _inventory.end()) {
		Item* item = it->second;
		_inventory.erase(it);
		return item;
	}
	sendObjectError("Can't pop item: ID " + std::to_string(id) + " not in player inventory.");
	return nullptr;
}

// * Remove an item from the player inventory. *
bool Player::removeItemFromInventory(ItemID id) {
	return _inventory.erase(id) > 0;
}

// * Check for an item in the player inventory. *
bool Player::checkItemInInventory(ItemID id) const {
	return _inventory.find(id) != _inventory.end();
}

// * Get the item by ID from the player inventory. *
const Item* Player::getItem(ItemID id) const {
	auto it = _inventory.find(id);
	if (it != _inventory.end()) {
		return it->second;
	}
	return nullptr;
}

	// * Get the item by ID from the player inventory. *
Item* Player::getItem(ItemID id) {
	return const_cast<Item*>(std::as_const(*this).getItem(id));
}

// * Get the ID of an item by its name. *
std::optional<ItemID> Player::getItemIdByName(const std::string& name) const {
	for (const auto& [id, item] : _inventory) {
		if (item && item->getName() == name) {
			return id;
		}
	}
	return std::nullopt;
}

// * Get the inventory of the player. *
std::string Player::getItemInInventory(bool add_details) const {
	if (_inventory.empty()) {
		return "No item in inventory.\n";
	}

	std::string inventory = "Item in " + this->getName() + "'s inventory: [";
	for (const auto& [id, item] : _inventory) {
		if (item) {
			if (add_details)
				inventory += "[";

			inventory += "\"" + item->getName();
			inventory += "\", ";

			if (add_details) {
				inventory += "\"" + item_type_to_string(item->getType());
				inventory += "\"], ";
			}
		}
	}

	inventory.pop_back();
	inventory.pop_back();
	inventory += "]";

	return inventory;
}
