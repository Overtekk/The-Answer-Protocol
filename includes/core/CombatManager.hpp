/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CombatManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:07:55 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/09 11:23:52 by roandrie         ###   ########.fr       */
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

		inline static constexpr float	BONUS_CHANCE_MULTIPLIER = 0.66f;
		inline static constexpr float	BASE_LUCK_FLEE = 0.5f;
		inline static constexpr float	BASE_RATIO_ENEMY_HP_FLEE = 20.0f;
		inline static constexpr float	BASE_RATIO_PLAYER_HP_FLEE = 15.0f;
		inline static constexpr float	MIN_FLEE_CHANCE = 20.0f;
		inline static constexpr float	MAX_FLEE_CHANCE = 90.0f;
		std::mt19937	_rng;

	public :
		// --- CONSTRUCTOR ---
		CombatManager(DialogueManager& dialogue_manager);
		// --- DESTRUCTOR ---
		~CombatManager() = default;

		// INIT & FINISH
		const std::string	initBattle(Player* player, Entity* entity);
		void				finishBattle(Player* player);

		// BATTLE STATUS
		const std::string	getBattleStats(Player* player, Entity* entity) const;
		CombatStatus		getBattleStatus(Player* player, Entity* entity) const;

		// MESSAGES
		const std::string	getCheckMsg(Entity* entity) const;

		// ATTACK
		const std::string	playerBasicAttack(Player* player, Entity* entity);
		const std::string	enemyBasicAttack(Player* player, Entity* entity);

		// RUNAWAY
		bool	tryFlee(Player* player, Entity* entity);
};
