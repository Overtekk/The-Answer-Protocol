/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuestManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:28:33 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/19 17:54:12 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <unordered_map>

# include "config/WorldConfig.hpp"


class QuestManager {
	private :
	std::unordered_map<std::string, QuestConfig>	_quests_dict;

	public :
		// CONSTRUCTOR
		QuestManager(const std::unordered_map<std::string, QuestConfig>& quests_config);
		// DESTRUCTOR
		~QuestManager() = default;
};
