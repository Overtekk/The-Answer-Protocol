/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 14:06:10 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/25 09:37:41 by roandrie         ###   ########.fr       */
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
		std::tuple<float, float> _position = {0.0f, 0.0f};
		fs::path _sprite;

	protected :
		float speed = 100.0f;
		float dx = 0;
		float dy = 0;

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
		std::tuple<float, float> getPos() const;
		bool setPos(std::tuple<float, float> new_pos);
		void set_direction(float new_dx, float new_dy);

		// Sprite
		fs::path getSpritePath() const { return _sprite; }

		virtual void update(float delta_time);

		// Error
		std::string sendObjectError(std::string error) const;
};
