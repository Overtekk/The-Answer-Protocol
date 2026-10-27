/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DialogueManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:04:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/27 11:16:27 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <optional>
# include <string>
# include <unordered_map>

# include "config/WorldConfig.hpp"
# include "core/DialogueManager.hpp"
# include "utils.h"

// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
DialogueManager::DialogueManager(const std::unordered_map<std::string, EntityConfig>& entity_map) {
	for (const auto& [id, entity] : entity_map) {
		_dialogue_map[id] = entity.dialogue;
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
