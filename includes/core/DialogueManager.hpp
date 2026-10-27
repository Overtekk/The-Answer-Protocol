/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DialogueManager.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 08:55:12 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/27 11:16:29 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <optional>
# include <string>
# include <unordered_map>

# include "config/WorldConfig.hpp"


class DialogueManager {
	private :
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>>	_dialogue_map;

		// --- METHODS ---
		const std::string*	findLine(const std::string& entity_id, const std::string& dialogue_key) const;

	public :
		// --- CONSTRUCTOR ---
		DialogueManager(const std::unordered_map<std::string, EntityConfig>& entity_map);
		// --- DESTRUCTOR ---
		~DialogueManager() = default;

		// --- METHODS ---
		bool						hasKey(const std::string& entity_id, const std::string& dialogue_key) const;
		std::optional<std::string>	getLine(const std::string& entity_id, const std::string& dialogue_key) const;
};
