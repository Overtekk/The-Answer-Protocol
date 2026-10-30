/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DialogueManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:04:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/30 15:42:22 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <optional>
# include <string>
# include <unordered_map>

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
		}
	}
}

// ============================================================================
// =====================          PUBLIC      =================================
// ============================================================================
// * Check if the entity has the dialogue key (silent: can be used as a probe). *
bool	DialogueManager::hasKey(const std::string& entity_id, const std::string& dialogue_key) const {
	return findLine(entity_id, dialogue_key) != nullptr;
}

// * Return the dialogue string of the entity if exist. *
std::optional<std::string>	DialogueManager::getLine(const std::string& entity_id, const std::string& dialogue_key) const {
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
