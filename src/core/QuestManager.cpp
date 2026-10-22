/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuestManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:28:21 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/21 15:35:58 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include <unordered_map>
# include <vector>

# include "core/QuestManager.hpp"
# include "config/WorldConfig.hpp"
# include "base_class/entities/Player.hpp"
# include "utils.h"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
QuestManager::QuestManager(const std::unordered_map<std::string, QuestConfig>& quests_config):
	_quests_dict(quests_config) {}

// ============================================================================
// ====================       PUBLIC METHODS      =============================
// ============================================================================
// * Quest the name and the description of a quest. *
const std::unordered_map<std::string, std::string>	QuestManager::getQuestInformation(const std::string& quest_id) const {
	std::unordered_map<std::string, std::string>	quest_info;

	if (checkQuestExist(quest_id)) {
		quest_info["name"] = _quests_dict.at(quest_id).name;
		quest_info["description"] = _quests_dict.at(quest_id).description;
		return quest_info;
	}
	return quest_info;
}

// * Give a quest to a player. *
bool		QuestManager::giveQuest(const std::string& quest_id,  Player& player) {
	if (checkQuestExist(quest_id)) {
		player.addQuest(quest_id);
		return true;
	}
	return false;
}

// * Remove a quest from a player. *
bool		QuestManager::removeQuest(const std::string& quest_id,  Player& player) {
	if (checkQuestExist(quest_id)) {
		player.removeQuest(quest_id);
		return true;
	}
	return false;
}

// * Make a quest complete. *
void		QuestManager::setQuestCompleted(const std::string& quest_id, Player& player) {
	if (checkIfPlayerHaveQuest(quest_id, player)) {
		player.setQuestCompleted(quest_id);
	}
}

// * Check if a player have the quest. *
bool		QuestManager::checkIfPlayerHaveQuest(const std::string& quest_id, Player& player, bool search_completed_quests) {
	if (checkQuestExist(quest_id)) {
		std::vector<std::string> player_quests;
		if (search_completed_quests) {
			player_quests = player.getCompletedQuests();
		}
		else {
			player_quests = player.getCurrentQuests();
		}
		for (const std::string& quest : player_quests) {
			if (quest == quest_id)
				return true;
		}
	}
	return false;
}

// * Add the quests marked as "spawn_with_quest". *
void	QuestManager::addDefaultQuests(Player& player) {
	for (const auto& it : _quests_dict) {
		if (it.second.spawn_with_quest)
			player.addQuest(it.first);
	}
}

// ============================================================================
// ====================       PRIVATE METHODS      ============================
// ============================================================================
// * Check if the requested quest exist. *
bool	QuestManager::checkQuestExist(const std::string& quest_id) const {
	auto it = _quests_dict.find(quest_id);
	if (it == _quests_dict.end()) {
		print_log("\"" + quest_id + "\"" " doesn't exist.");
		return false;
	}

	return true;
}
