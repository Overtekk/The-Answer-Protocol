/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualEntity.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:31:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 14:40:49 by nbuchy           ###   ########.fr       */
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
		// Rectangle init_sprite_rect();
		// int _current_frame = 0;
		// float _frame_timer;
		Animation				_idle;
		Animation				_walk_down;
		Animation				_walk_up;
		Animation				_walk_lr; // Animation when you walk on the right or left (it will be flipped)
		//bool 					_facing_left = true;
		EntityDirection 		_direction_row = EntityDirection::NONE;

		// Movement
		float _speed = 100.0f;
		float _dx = 0; // entity x direction -1 = left, 1 = right, 0 = None
		float _dy = 0; // entity y direction -1 = up, 1 = down, 0 = None

	protected :
		virtual void update_movement(float delta_time);
		virtual void update_sprite();

	public :
		VisualEntity(const Entity& entity, std::string texture, std::tuple<int, int> sprite_dim, float scale = 1.0f);

		virtual ~VisualEntity();

		// Protection against copying texture
		VisualEntity(const VisualEntity&) = delete;
		VisualEntity& operator=(const VisualEntity&) = delete;

		virtual void update(float delta_time);

		// Draw
		void on_draw();
		// void unload_texture();

		// Position
		Vector2 getPos() const;
		bool setPos(Vector2 new_pos);
		void set_direction(float new_dx, float new_dy);

		// Error
		void sendObjectError(std::string error);
};
