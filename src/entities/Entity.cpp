/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:06:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/10 10:59:46 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <algorithm>
# include <string>

# include "base_class/entities/Entity.hpp"
#include "config/Enums.hpp"
# include "utils.h"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
Entity::Entity(const std::string& id, const std::string& name, const std::string& description,
	EnemyType type, int health):
	_id(id),
	_description(description),
	_health(std::clamp(health, 1, 1000)),
	_type(type),
	_name(name) {
		_max_health = health;
	}

// ============================================================================
// =====================           GETTER      ================================
// ============================================================================
const std::string&	Entity::getID() const { return _id; }

const std::string&	Entity::getName() const { return _name; }

int 				Entity::getHealth() const { return _health; }

int					Entity::getMaxHealth() const { return _max_health; }

EnemyType 			Entity::getType() const { return _type; }

bool				Entity::inCombat() { return _in_combat; }

int					Entity::getAttackValue() const { return _attack; }

const std::string&	Entity::getZone() const { return _zone; }

EnemyBehavior		Entity::getBehavior() const { return _behavior; }

// ============================================================================
// =====================           SETTER      ================================
// ============================================================================
void	Entity::setHealth(int new_value) { _health = std::max(0, new_value); }

void	Entity::setCombat(bool new_state) { _in_combat = new_state; }

void	Entity::setAttackValue(int new_value) { _attack = std::max(0, new_value); }

void	Entity::setZone(const std::string& new_zone) { _zone = new_zone; }

void	Entity::setBehavior(EnemyBehavior new_behavior) { _behavior = new_behavior; }

// ============================================================================
// =====================           ERROR      =================================
// ============================================================================
void Entity::sendObjectError(const std::string& error) const {
	print_log(" ERROR: " + error + "\n");
}
