/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:06:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/21 14:42:12 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/entities/Entity.hpp"

Entity::Entity(
	const std::string& name, const fs::path& sprite, int health
):
	_name(name),
	_health(std::clamp(health, 0, 1000)),
	_sprite(sprite) {}

// Getter

std::string Entity::getName() const { return _name; }

int Entity::getHealth() const { return _health;  }

std::tuple<int, int> Entity::getPos() const { return _position; }

 // Setter

bool Entity::setName(std::string& new_name) {
	if (new_name.length() >= 3 && new_name.length() <= 20) {
		_name = new_name;
		return true;
	}
	sendObjectError("Can't modify name. Minimum 3 and maximum 20 characters.");
	return false;
}

bool Entity::setHealth(int new_value) {
	_health = std::clamp(new_value, 0, 1000);
	return true;
}

bool Entity::setPos(std::tuple<int, int> new_pos) {
	if (std::get<0>(new_pos) < 0 || std::get<1>(new_pos) < 0) {
		sendObjectError("Position can't be negative.");
		return false;
	}
	_position = new_pos;
	return true;
}

// Error
std::string Entity::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}
