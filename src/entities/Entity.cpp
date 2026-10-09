/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:06:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 11:56:05 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <algorithm>
# include <string>

# include "base_class/entities/Entity.hpp"
# include "utils.h"


// --- CONSTRUCTOR ---
Entity::Entity(const std::string& id, const std::string& name, const std::string& description,
	EnemyType type, int health):
	_id(id),
	_description(description),
	_health(std::clamp(health, 0, 1000)),
	_type(type),
	_name(name) {}

// --- GETTER ---
const std::string&	Entity::getName() const { return _id; }
const std::string&	Entity::getName() const { return _name; }
int 		Entity::getHealth() const { return _health;  }
EnemyType 	Entity::getType() const { return _type; }

// --- ERROR ---
void Entity::sendObjectError(const std::string& error) const {
	print_log(" ERROR: " + error + "\n");
}
