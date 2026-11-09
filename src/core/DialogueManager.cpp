/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DialogueManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:04:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/09 12:50:29 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <optional>
# include <string>
# include <unordered_map>
# include <random>

#include "config/Enums.hpp"
# include "config/WorldConfig.hpp"
# include "core/DialogueManager.hpp"
# include "utils.h"

// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
DialogueManager::DialogueManager(const std::unordered_map<std::string, EntityConfig>& entity_map) {
	for (const auto& [id, entity] : entity_map) {
		_dialogue_map[id] = entity.dialogue;

		// if dialogue stage exist
		if (!entity.dialogue_stage.empty()) {
			_stages_map[id] = entity.dialogue_stage;
		}
		else {
			int count = 0;
			// check if entity has dialogue and create the stage
			while (entity.dialogue.find("talk_" + std::to_string(count + 1)) != entity.dialogue.end())
				count++;
			if (count > 0) {
				DialogueStage stage;
				stage.last_stage = count;
				stage.quest_id = "";
				stage.condition = QuestStage::UNKNOWN;
				_stages_map[id].push_back(stage);
			}

			// get the "neutral_" dialogue
			count = 0;
			while (entity.dialogue.find("neutral_" + std::to_string(count + 1)) != entity.dialogue.end())
				count++;
			if (count > 0)
				_neutral_count_map[id] = count;
		}
	}
}

// ============================================================================
// =====================          PUBLIC      =================================
// ============================================================================
// --- MAIN LOGIC ---
// * Check if the entity has the dialogue key (silent: can be used as a probe). *
bool								DialogueManager::hasKey(const std::string& entity_id, const std::string& dialogue_key) const {
	return findLine(entity_id, dialogue_key) != nullptr;
}

// * Return the dialogue string of the entity if exist. *
std::optional<std::string>			DialogueManager::getLine(const std::string& entity_id, const std::string& dialogue_key) const {
	const std::string*	line = findLine(entity_id, dialogue_key);
	if (!line) {
		print_log("DialogueManager: can't find dialogue \"" + dialogue_key + "\" for entity \"" + entity_id + "\".");
		return std::nullopt;
	}

	return *line;
}

// Get a dialogue stage from an entity. *
const std::vector<DialogueStage>&	DialogueManager::getStages(const std::string& entity_id) const {
	const auto& it = _stages_map.find((entity_id));
	if (it == _stages_map.end())
		return _empty_stages;
	return it->second;
}

// --- GETTER ---
const std::string	DialogueManager::getEncounterDialogue(const std::string& entity_id) const {
	std::optional<std::string> result = getLine(entity_id, "encounter");
	if (result)
		return *result;
	return entity_id + " is here!";
}

const std::string	DialogueManager::getCheckDialogue(const std::string &entity_id) const {
	std::optional<std::string> result = getLine(entity_id, "check_default");
	if (result)
		return *result;
	return entity_id;
}

const std::string	DialogueManager::getNeutralDialogue(const std::string &entity_id) const {
	const auto result = _neutral_count_map.find(entity_id);
	if (result == _neutral_count_map.end())
		return entity_id + " is watching at you.";

	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> dist(1, _neutral_count_map.size());
	int n = dist(gen);

	std::optional<std::string> result_line = getLine(entity_id, "neutral_" + std::to_string(n));
	return *result_line;
}

// ============================================================================
// =====================          PRIVATE      ================================
// ============================================================================
// * Return a pointer to the dialogue string, or nullptr if the entity or the key doesn't exist. *
const std::string*	DialogueManager::findLine(const std::string& entity_id, const std::string& dialogue_key) const {
	const auto it_entity = _dialogue_map.find(entity_id);
	if (it_entity == _dialogue_map.end())
		return nullptr;

	const auto it_key = it_entity->second.find(dialogue_key);
	if (it_key == it_entity->second.end())
		return nullptr;

	return &it_key->second;
}
