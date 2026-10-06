/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:06:10 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 11:43:44 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <algorithm>
# include <filesystem>
# include <string>
# include <tuple>
# include "config/Enums.hpp"

namespace fs = std::filesystem;

class Entity {
	private :
		std::string _name;
		std::string _description;
		int _health;
		fs::path _sprite;
		EnemyType _type;

	public :
		// Constructor
		Entity(
			const std::string& name, const std::string& description, const fs::path& sprite,
			EnemyType type, int health);

		// Destructor
		virtual ~Entity() = default;

		// Name
		std::string getName() const;
		bool setName(std::string& new_name);

		// Health
		int getHealth() const;
		bool setHealth(int new_value);

		// Sprite
		fs::path getSpritePath() const;

		// Type
		virtual EnemyType getType() const;

		// Error
		std::string sendObjectError(std::string error) const;
};
