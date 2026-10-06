/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:06:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 14:34:40 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/entities/Entity.hpp"
# include "utils.h"

// --- CONSTRUCTOR ---
Entity::Entity(
	const std::string& name, const std::string& description, const fs::path& sprite,
	EnemyType type, int health
):
	_name(name),
	_description(description),
	_health(std::clamp(health, 0, 1000)),
	_sprite(sprite),
	_type(type) {}

// --- GETTER ---
std::string Entity::getName() const { return _name; }
int 		Entity::getHealth() const { return _health;  }
EnemyType 	Entity::getType() const { return _type; }
fs::path 	Entity::getSpritePath() const {return _sprite; };

// --- SETTER ---
void		Entity::setHealth(int new_value) {
	if (0 > new_value) {
		sendObjectError("Health can't be negative.");
	}
	else if (new_value == 0) {
		pass;
	}
	_health = new_value;
}

// Error
std::string Entity::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}
