/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CombatManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:10:21 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/02 15:50:51 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <algorithm>
# include <random>
# include <string>

# include "core/CombatManager.hpp"
# include "base_class/entities/Player.hpp"
# include "base_class/entities/Entity.hpp"
# include "core/DialogueManager.hpp"
# include "config/Enums.hpp"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
CombatManager::CombatManager(DialogueManager& dialogue_manager):
	_dialogue_manager(dialogue_manager),
	_rng(std::random_device{}()) {}

// ============================================================================
// =====================         PUBLIC      ==================================
// ============================================================================
const std::string	CombatManager::initBattle(Player* player, Entity* entity) {
	player->setCombat(true);
	entity->setCombat(true);

	return _dialogue_manager.getEncounterDialogue(entity->getID());
}

void	CombatManager::finishBattle(Player *player) {
	player->setCombat(false);
}

const std::string	CombatManager::getBattleStats(Player *player, Entity *entity) const {
	std::string result = "{ YOU: HP: ";

	result += std::to_string(player->getHealth());
	result += "/";
	result += std::to_string(player->getMaxHealth());
	result += " | " + entity->getName() + ": HP: ";
	result += std::to_string(entity->getHealth());
	result += "/";
	result += std::to_string(entity->getMaxHealth());

	return result;
}

CombatStatus		CombatManager::getBattleStatus(Player *player, Entity *entity) const {
	if (player->getHealth() <= 0)
		return CombatStatus::PLAYER_LOSE;
	else if (entity->getHealth() <= 0)
		return CombatStatus::ENTITY_LOSE;
	return CombatStatus::NOTHING;
}

const std::string	CombatManager::PlayerBasicAttack(Player *player, Entity *entity) {
	float bonus_chance = std::clamp((player->getLuck() * BONUS_CHANCE_MULTIPLIER), 0.0f, 100.0f);
	std::uniform_int_distribution<int> roll_100(0, 99);

	Item* player_weapon = player->getEquippedWeapon();
	int bonus = 0;
	if (!player_weapon)
		bonus = 0;
	else {
		if (player_weapon->getBonusMax() > 0) {
			std::uniform_int_distribution<int> roll_bonus(player_weapon->getBonusMin(), player_weapon->getBonusMax());
			if (roll_100(_rng) < bonus_chance)
				bonus = roll_bonus(_rng);
		}
	}

	int damage = player->getAttackValue();
	damage += bonus;

	int result = (entity->getHealth() - damage);
	entity->setHealth(result);

	if (bonus > 0) {
		return "You attacked " + entity->getName() + " with a strength of " + std::to_string(damage) + " (bonus +" + std::to_string(bonus) + ").";
	}
	return "You attacked " + entity->getName() + " with a strength of " + std::to_string(damage) + ".";
}
