/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:06:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 13:11:46 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/entities/Entity.hpp"

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

// Error
std::string Entity::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}
