/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualEntity.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:31:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 15:15:08 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <tuple>
# include "raylib.h"
# include "base_class/entities/Entity.hpp"
# include "gui/Animation.hpp"

# define MAX_FRAME_SPEED 15
# define MIN_FRAME_SPEED 1

enum class EntityDirection
{
	NONE = 0,
	DOWN = 1,
	UP = 2,
	LEFT = 3,
	RIGHT = 4
};

class VisualEntity {
	private :
		// Reference to the entity
		const Entity& _entity;

		// Texture
		Texture2D				_img; // Texture
		std::tuple<int, int>	_sprite_dim;
		float					_sprite_scale;

		Vector2 _position = {0.0f, 0.0f};

		// Sprite frame
		Animation				_idle;
		Animation				_walk_down;
		Animation				_walk_up;
		Animation				_walk_lr; // Animation when you walk on the right or left (it will be flipped)
		EntityDirection 		_orientation = EntityDirection::NONE;

		// Movement
		float _speed = 100.0f;
		float _dx = 0; // entity x direction dx < 0 left, dx > 0 right, 0 = None
		float _dy = 0; // entity y direction dy < 0 up, dy > 0 down, 0 = None

	protected :
		// update direction (dx and dy) depending on your needs (key pressed...)
		virtual void updateMovement() = 0;

		// Update entity sprite
		virtual void updateSprite();

	public :
		VisualEntity(const Entity& entity,
			const std::string &texture,
			std::tuple<int, int>
			sprite_dim,
			float scale = 1.0f);

		virtual ~VisualEntity();

		// Protection against copying texture
		VisualEntity(const VisualEntity&) = delete;
		VisualEntity& operator=(const VisualEntity&) = delete;

		// Update entity position, orientation, and sprite
		virtual void update();

		// Utils

		// Return entity orientation (UP DOWN LEFT RIGHT NONE)
		EntityDirection getOrientation() const;
		// Set entity orientation 
		void setOrientation(EntityDirection orientation);
		
		// Draw
		
		// Draw entity sprits
		void onDraw();

		// Position

		// Return entity postion x en y
		const Vector2 &getPos() const;

		// Set entity position x and y
		void setPos(const Vector2 &new_pos);

		// Set entity direction (dx and dy)
		void setDirection(float new_dx, float new_dy);

		// Error
		void sendObjectError(const std::string &error);
};
