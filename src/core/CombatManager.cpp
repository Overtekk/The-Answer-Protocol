/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CombatManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:10:21 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/09 12:19:31 by roandrie         ###   ########.fr       */
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

void				CombatManager::finishBattle(Player *player) {
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

const std::string	CombatManager::getCheckMsg(Entity *entity) const { return _dialogue_manager.getCheckDialogue(entity->getID()); }

// ATTACK
const std::string	CombatManager::playerBasicAttack(Player *player, Entity *entity) {
	// player chance
	float bonus_chance = std::clamp((player->getLuck() * BONUS_CHANCE_MULTIPLIER), 0.0f, 100.0f);

	// get the weapon of the player
	Item* player_weapon = player->getEquippedWeapon();
	int bonus = 0;
	if (!player_weapon)
		bonus = 0;
	else {
		// get bonus stats of weapon
		if (player_weapon->getBonusMax() > 0) {
			std::uniform_int_distribution<int> roll_bonus(player_weapon->getBonusMin(), player_weapon->getBonusMax());
			std::uniform_int_distribution<int> roll_100(0, 99);
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

const std::string	CombatManager::enemyBasicAttack(Player *player, Entity *entity) {
	// player chance
	float bonus_chance = std::clamp((player->getLuck() * BONUS_CHANCE_MULTIPLIER), 0.0f, 100.0f);

	int	entity_damage = entity->getAttackValue();

	// get random value from player defense
	int player_defense = 0;
	if (player->getDefense() > 0) {
		std::uniform_int_distribution<int> roll_bonus(0, player->getDefense());
		std::uniform_int_distribution<int> roll_100(0, 99);
		if (roll_100(_rng) < bonus_chance) {
			player_defense = roll_bonus(_rng);
		}
	}

	int total_damage = entity_damage - player_defense;

	if (total_damage > 0) {
		player->setHealth(player->getHealth() - total_damage);
		return entity->getName() + " attacked you with a strength of " + std::to_string(total_damage);
	}
	return "You blocked " + entity->getName() + " damage.";
}

// RUNAWAY
bool				CombatManager::tryFlee (Player *player, Entity *entity) {
	// base chance
	float flee_base_chance = 50.0f;
	// calculate fluctuations:
	// - add player chance
	// - add ratio enemy based on health (more health = less chance)
	// - add ratio player based on health (less health = more chance)
	float player_bonus_chance = player->getLuck() * BASE_LUCK_FLEE;
	float ratio_enemy = ((static_cast<float>(entity->getHealth()) / entity->getMaxHealth()) * BASE_RATIO_ENEMY_HP_FLEE);
	float ratio_player = ((static_cast<float>(player->getHealth()) / player->getMaxHealth()) * BASE_RATIO_PLAYER_HP_FLEE);
	flee_base_chance += player_bonus_chance - ratio_enemy - ratio_player;

	// get the final percentage
	float final_chance = std::clamp(flee_base_chance, MIN_FLEE_CHANCE, MAX_FLEE_CHANCE);

	// roll the dice
	std::uniform_int_distribution<int> roll_100(0, 99);
	if (roll_100(_rng) < final_chance)
		return true;
	return false;
}
