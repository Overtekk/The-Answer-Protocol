/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DialogueManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 08:55:12 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/09 12:43:17 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <optional>
# include <string>
# include <unordered_map>
# include <vector>

# include "config/WorldConfig.hpp"


class DialogueManager {
	private :
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>>	_dialogue_map;
		std::unordered_map<std::string, std::vector<DialogueStage>>						_stages_map;
		std::vector<DialogueStage>														_empty_stages;

		std::unordered_map<std::string, int>	_neutral_count_map;

		// --- METHODS ---
		const std::string*	findLine(const std::string& entity_id, const std::string& dialogue_key) const;

	public :
		// --- CONSTRUCTOR ---
		DialogueManager(const std::unordered_map<std::string, EntityConfig>& entity_map);
		// --- DESTRUCTOR ---
		~DialogueManager() = default;

		// --- METHODS ---
		bool								hasKey(const std::string& entity_id, const std::string& dialogue_key) const;
		std::optional<std::string>			getLine(const std::string& entity_id, const std::string& dialogue_key) const;
		const std::vector<DialogueStage>&	getStages(const std::string& entity_id) const;

		const std::string	getEncounterDialogue(const std::string& entity_id) const;
		const std::string	getCheckDialogue(const std::string& entity_id) const;
		const std::string	getNeutralDialogue(const std::string& entity_id) const;
};
