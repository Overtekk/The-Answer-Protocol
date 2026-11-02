/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CombatManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:07:55 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/02 14:54:35 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <random>

# include "base_class/entities/Player.hpp"
# include "base_class/entities/Entity.hpp"
# include "core/DialogueManager.hpp"
# include "config/Enums.hpp"


class CombatManager {
	private :
		DialogueManager&	_dialogue_manager;

		inline static constexpr float	BONUS_CHANCE_MULTIPLIER = 0.66;
		std::mt19937	_rng;

	public :
		// --- CONSTRUCTOR ---
		CombatManager(DialogueManager& dialogue_manager);
		// --- DESTRUCTOR ---
		~CombatManager() = default;

		const std::string	initBattle(Player* player, Entity* entity);
		void				finishBattle(Player* player);
		const std::string	getBattleStats(Player* player, Entity* entity) const;
		CombatStatus	getBattleStatus(Player* player, Entity* entity) const;

		// ATTACK
		const std::string	PlayerBasicAttack(Player* player, Entity* entity);
};
