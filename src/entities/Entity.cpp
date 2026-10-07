/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:06:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/07 12:01:49 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/entities/Entity.hpp"
# include "utils.h"

// --- CONSTRUCTOR ---
Entity::Entity(const std::string& name, const std::string& description, EnemyType type, int health):
	_name(name),
	_description(description),
	_health(std::clamp(health, 0, 1000)),
	_type(type) {}

// --- GETTER ---
std::string Entity::getName() const { return _name; }
int 		Entity::getHealth() const { return _health;  }
EnemyType 	Entity::getType() const { return _type; }

// Error
void Entity::sendObjectError(std::string error) const {
	print_log(" ERROR: " + error + "\n");
}
