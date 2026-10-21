/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuestManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:28:33 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/21 15:36:00 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <unordered_map>

# include "config/WorldConfig.hpp"

class Player;


class QuestManager {
	private :
	std::unordered_map<std::string, QuestConfig>	_quests_dict;

		bool	checkQuestExist(const std::string& quest_id) const;

	public :
		// CONSTRUCTOR
		QuestManager(const std::unordered_map<std::string, QuestConfig>& quests_config);
		// DESTRUCTOR
		~QuestManager() = default;

		const std::unordered_map<std::string, std::string>	getQuestInformation(const std::string& quest_id) const;
		bool		giveQuest(const std::string& quest_id, Player& player);
		bool		removeQuest(const std::string& quest_id, Player& player);
		void		setQuestCompleted(const std::string& quest_id, Player& player);
		bool		checkIfPlayerHaveQuest(const std::string& quest_id, Player& player, bool search_completed_quests = false);

		void		addDefaultQuests(Player& player);
};
