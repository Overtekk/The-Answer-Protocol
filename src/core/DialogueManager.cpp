/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DialogueManager.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 09:04:57 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/27 10:46:14 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <optional>
# include <string>
# include <unordered_map>

# include "config/WorldConfig.hpp"
# include "core/DialogueManager.hpp"

// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
DialogueManager::DialogueManager(const std::unordered_map<std::string, EntityConfig>& entity_map)
	{
		for (const auto& [id, entity] : entity_map) {
			_dialogue_map[id] = entity.dialogue;
		}
}

// ============================================================================
// =====================          PUBLIC      =================================
// ============================================================================
// * Return the dialogue string of the entity if exist. *
std::optional<std::string>	DialogueManager::getLine(const std::string entity_id, const std::string dialogue_key) {
	if (!hasKey(entity_id, dialogue_key))
		return "";

	return _dialogue_map[entity_id][dialogue_key];
}

// ============================================================================
// =====================          PRIVATE      ================================
// ============================================================================
// * Check if the entity has the dialogue key. *
bool	DialogueManager::hasKey(const std::string entity_id, const std::string dialogue_key) {
	const auto it = _dialogue_map[entity_id].find(dialogue_key);
	if (it == _dialogue_map[entity_id].end())
		return false;
	return true;
}
