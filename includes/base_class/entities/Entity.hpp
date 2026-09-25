/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:06:10 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/25 10:42:42 by roandrie         ###   ########.fr       */
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

		// Sprite
		fs::path getSpritePath() const { return _sprite; }

		// Error
		std::string sendObjectError(std::string error) const;
};
