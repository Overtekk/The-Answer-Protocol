/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:06:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/21 16:43:42 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/entities/Entity.hpp"

Entity::Entity(
	const std::string& name, const fs::path& sprite, int health
):
	_name(name),
	_health(std::clamp(health, 0, 1000)),
	_sprite(sprite) {}

void Entity::update(float delta_time) {
	std::get<0>(_position) = dx * speed * delta_time;
	std::get<1>(_position) = dy * speed * delta_time;
	dx, dy = 0.0f, 0.0f;
};

// Getter

std::string Entity::getName() const { return _name; }

int Entity::getHealth() const { return _health;  }

std::tuple<float, float> Entity::getPos() const { return _position; }

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

bool Entity::setPos(std::tuple<float, float> new_pos) {
	if (std::get<0>(new_pos) < 0 || std::get<1>(new_pos) < 0) {
		sendObjectError("Position can't be negative.");
		return false;
	}
	_position = new_pos;
	return true;
}

void Entity::set_direction(float new_dx, float new_dy) {
	dx = std::clamp(new_dx, -1.0f, 1.0f);
	dy = std::clamp(new_dy, -1.0f, 1.0f);
}

// Error
std::string Entity::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}
