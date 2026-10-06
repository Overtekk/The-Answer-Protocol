/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:06:10 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 14:45:49 by roandrie         ###   ########.fr       */
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

// * ABSTRACT CLASS *
class Entity {
	protected :
		std::string _name;

	private :
		std::string _description;
		int 		_health;
		fs::path	_sprite;
		EnemyType	_type;

	public :
		// --- CONSTRUCTOR ---
		Entity(
			const std::string& name, const std::string& description, const fs::path& sprite,
			EnemyType type, int health);
		// --- DESTRUCTOR ---
		virtual ~Entity() = default;

		// --- GETTER ---
		std::string 		getName() const;
		int 				getHealth() const;
		fs::path			getSpritePath() const;
		virtual EnemyType	getType() const;

		// --- SETTER ---
		void				setHealth(int new_value);

		// --- ERROR ---
		void sendObjectError(std::string error) const;
};
