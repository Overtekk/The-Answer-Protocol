/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuestManager.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 10:28:21 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/19 17:51:37 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "core/QuestManager.hpp"
# include "config/WorldConfig.hpp"

// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
QuestManager::QuestManager(const std::unordered_map<std::string, QuestConfig>& quests_config):
	_quests_dict(quests_config) {}
