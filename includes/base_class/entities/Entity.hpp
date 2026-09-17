/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:06:10 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/17 16:11:09 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <iostream>
# include <algorithm>

class Entity {
	private :
	std::string _name;
	int _health;

	public :
		// Constructor
		Entity(const std::string& name, int health)
        : _name(name), _health(std::clamp(health, 0, 1000)) {}

		// Destructor
		virtual ~Entity() = default;

		std::string getName() const;
		void setName(std::string&);

		int getHealth() const;
		void setHealth(int);

		virtual void test() = 0;
};

// Getter

inline std::string Entity::getName() const {
	return _name;
}

inline int Entity::getHealth() const {
	return _health;
}

 // Setter

inline void Entity::setName(std::string& new_name) {
	if (new_name.length() >= 3 && new_name.length() <= 20)
		_name = new_name;
}

inline void Entity::setHealth(int new_value) {
	_health = std::clamp(new_value, 0, 1000);
}
