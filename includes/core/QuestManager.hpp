/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuestManager.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:28:33 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/19 17:27:57 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <unordered_map>


class QuestManager {
	private :
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>>	_quests_dict;

	public :
		// CONSTRUCTOR
		QuestManager(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>	_quests_dict);
		// DESTRUCTOR
		~QuestManager() = default;
};
