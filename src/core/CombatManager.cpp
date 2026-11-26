/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CombatManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:10:21 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/26 13:56:46 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <algorithm>
# include <random>
# include <string>

# include "core/CombatManager.hpp"
# include "base_class/entities/Player.hpp"
# include "base_class/entities/Entity.hpp"
# include "base_class/entities/Enemy.hpp"
# include "core/DialogueManager.hpp"
# include "config/Enums.hpp"
# include "config/config_messages.h"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
CombatManager::CombatManager(DialogueManager& dialogue_manager):
	_dialogue_manager(dialogue_manager),
	_rng(std::random_device{}()) {}


// ============================================================================
// =====================         PUBLIC      ==================================
// ============================================================================
// INIT & FINISH
const std::string	CombatManager::initCombat(Player* player, Entity* entity) {
	player->setCombat(true);
	entity->setCombat(true);

	return _dialogue_manager.getEncounterDialogue(entity->getID());
}


void				CombatManager::finishCombat(Player *player) { player->setCombat(false); }


// COMBAT STATUS
const std::string	CombatManager::getCombatStats(Player *player, Entity *entity) const {
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


CombatStatus		CombatManager::getCombatStatus(Player *player, Entity *entity) const {
	if (player->getHealth() <= 0)
		return CombatStatus::PLAYER_LOSE;
	else if (entity->getHealth() <= 0)
		return CombatStatus::ENTITY_LOSE;
	return CombatStatus::NOTHING;
}


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

	Enemy* enemy = dynamic_cast<Enemy*>(entity);
	if (enemy && enemy->hasBeenAttacked() == false)
		enemy->changeAttackedState(true);

	return actPlayerAttack(entity->getName(), damage, bonus);
}


const std::string	CombatManager::enemyBasicAttack(Player *player, Entity *entity) {
	setRandomSparedStatus(entity);

	// player chance
	float bonus_chance = std::clamp((player->getLuck() * BONUS_CHANCE_MULTIPLIER), 0.0f, 100.0f);

	int	entity_damage = entity->getAttackValue();

	if (entity_damage <= 0)
		return actEnemyNoDamage(entity->getName());

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
		return actEnemyAttack(entity->getName(), total_damage);
	}
	return actPlayerBlocked(entity->getName());
}


// ACT
ActReturn	CombatManager::enemyAct(Entity *entity, const std::string& action) {
	ActReturn	result;

	switch (entity->getBehavior()) {
		case EnemyBehavior::BASIC:			result = actDefault(entity, action);	break;
		case EnemyBehavior::VIROVIROKUN:	result = actDefault(entity, action);	break;
		case EnemyBehavior::MAUS:			result = actDefault(entity, action);	break;
		case EnemyBehavior::KAWKAW:			result = actDefault(entity, action);	break;
		case EnemyBehavior::SWATCHLINGS:	result = actDefault(entity, action);	break;
		case EnemyBehavior::K_ROUND:		result = actDefault(entity, action);	break;
		case EnemyBehavior::GUARD_DOG:		result = actDefault(entity, action);	break;
		case EnemyBehavior::QUEEN:			result = actDefault(entity, action);	break;
	}

	return result;
}


// TURN
const std::string	CombatManager::enemyTurn(Player* player, Entity* entity) {
	std::string	result;

	switch (entity->getBehavior()) {
		case EnemyBehavior::BASIC:			result = enemyBasicAttack(player, entity);	break;
		case EnemyBehavior::VIROVIROKUN:	result = enemyBasicAttack(player, entity);	break;
		case EnemyBehavior::MAUS:			result = enemyBasicAttack(player, entity);	break;
		case EnemyBehavior::KAWKAW:			result = enemyBasicAttack(player, entity);	break;
		case EnemyBehavior::SWATCHLINGS:	result = enemyBasicAttack(player, entity);	break;
		case EnemyBehavior::K_ROUND:		result = enemyBasicAttack(player, entity);	break;
		case EnemyBehavior::GUARD_DOG:		result = enemyBasicAttack(player, entity);	break;
		case EnemyBehavior::QUEEN:			result = enemyBasicAttack(player, entity);	break;
	}

	return result;
}


// SPARE
bool				CombatManager::trySpare(Entity *entity) {
	Enemy* enemy = dynamic_cast<Enemy*>(entity);
	if (!enemy)
		return false;

	if (enemy->getCanBeSparedState()) {
		enemy->changeSparedState(true);
		return true;
	}

	return false;
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


// REWARDS
const std::string	CombatManager::rewardsPlayer(Player *player, Enemy *enemy) {
	std::uniform_int_distribution<int> roll_base_money(10, 20);
	int money_earn = roll_base_money(_rng);

	// SPARED
	if (enemy->hasBeenSpared()) {
		std::uniform_int_distribution<int> roll_bonus_spared(5, 10);
		money_earn += roll_bonus_spared(_rng);
	}

	// ENEMY TYPE
	if (enemy->getType() == EnemyType::ENEMY) {
		std::uniform_int_distribution<int> roll_bonus_enemy_type(5, 10);
		money_earn += roll_bonus_enemy_type(_rng);
	}
	else if (enemy->getType() == EnemyType::BOSS) {
		std::uniform_int_distribution<int> roll_bonus_boss_type(11, 22);
		money_earn += roll_bonus_boss_type(_rng);
	}

	// HEALTH BONUS
	if (enemy->getMaxHealth() >= 200) {
		std::uniform_int_distribution<int> roll_bonus_enemy_hp(3, 9);
		money_earn += roll_bonus_enemy_hp(_rng);
	}

	player->setMoney(player->getMoney() + money_earn);

	return "You earn " + std::to_string(money_earn) + "$";
}


// ============================================================================
// =====================         PRIVATE      =================================
// ============================================================================

bool		CombatManager::setRandomSparedStatus(Entity *entity) {
	Enemy* enemy = dynamic_cast<Enemy*>(entity);
	if (!enemy)
		return false;

	if (enemy->hasBeenAttacked())
		return false;

	std::uniform_int_distribution<int> roll_100(0, 99);
	float spare_chance = 33;
	if (roll_100(_rng) >= spare_chance)
		return false;

	enemy->setCanBeSparedState(true);
	return true;

}


ActReturn	CombatManager::actDefault(Entity *entity, const std::string &action) {
	ActReturn result = {};
	Enemy* enemy = dynamic_cast<Enemy*>(entity);
	if (!enemy)
		return result;

	if (action == "talk")
		result.message = actDefaultActTalk(enemy->getName());

	else if (action == "check") {
		if (enemy->getCanBeSparedState())
			result.message = _dialogue_manager.getCanSpareText(enemy->getID());

		else if (enemy->getMaxHealth() / 3 > enemy->getHealth())
			result.message = _dialogue_manager.getLowHPText(enemy->getID());

		else
			result.message = _dialogue_manager.getCheckDialogue(enemy->getID());
	}

	else {
		result.message = "Actions: TALK, CHECK";
		result.next_turn = false;
	}

	return result;
}
