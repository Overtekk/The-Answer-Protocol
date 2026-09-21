/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:06:10 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/21 14:50:53 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <iostream>
# include <algorithm>
# include <filesystem>
# include <string>
# include <tuple>

namespace fs = std::filesystem;

class Entity {
	private :
		std::string _name;
		int _health;
		std::tuple<int, int> _position;
		fs::path _sprite;

	public :
		// Constructor
		Entity(const std::string& name, const fs::path& sprite, int health);

		// Destructor
		virtual ~Entity() = default;

		// Name
		std::string getName() const;
		bool setName(std::string& new_name);

		// Health
		int getHealth() const;
		bool setHealth(int new_value);

		// Position
		std::tuple<int, int> getPos() const;
		bool setPos(std::tuple<int, int> new_pos);

		// Sprite
		fs::path getSpritePath() const { return _sprite; }

		// virtual void test() = 0;

		// Error
		std::string sendObjectError(std::string error) const;
};
