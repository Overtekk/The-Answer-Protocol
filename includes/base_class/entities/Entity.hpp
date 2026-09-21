/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:06:10 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/21 10:36:31 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <iostream>
# include <algorithm>
# include <filesystem>
# include <tuple>

namespace fs = std::filesystem;

class Entity {
	private :
	std::string _name;
	int _health;
	std::tuple<int, int> _position;

	public :
		// Constructor
		Entity(const std::string& name, const fs::path& sprite, int health)
        : _name(name),  _health(std::clamp(health, 0, 1000)), sprite(sprite) {}

		// Destructor
		virtual ~Entity() = default;

		// Path to sprite
		fs::path sprite;

		// Name
		std::string getName() const { return _name; }
		bool setName(std::string& new_name);

		// Health
		int getHealth() const { return _health;  }
		bool setHealth(int new_value);

		// Position
		std::tuple<int, int> getPos() const { return _position; }
		bool setPos(std::tuple<int, int> new_pos);

		// virtual void test() = 0;

		// Error
		std::string sendObjectError(std::string error) const;
};

 // Setter

inline bool Entity::setName(std::string& new_name) {
	if (new_name.length() >= 3 && new_name.length() <= 20) {
		_name = new_name;
		return true;
	}
	sendObjectError("Can't modify name. Minimum 3 and maximum 20 characters.");
	return false;
}

inline bool Entity::setHealth(int new_value) {
	_health = std::clamp(new_value, 0, 1000);
	return true;
}

inline bool Entity::setPos(std::tuple<int, int> new_pos) {
	if (std::get<0>(new_pos) < 0 || std::get<1>(new_pos) < 0) {
		sendObjectError("Position can't be negative.");
		return false;
	}
	_position = new_pos;
	return true;
}

// Error
inline std::string Entity::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}
