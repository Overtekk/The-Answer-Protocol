/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualEntity.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:31:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/25 11:45:55 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <tuple>
# include "raylib.h"
# include "base_class/entities/Entity.hpp"

# define MAX_FRAME_SPEED 15
# define MIN_FRAME_SPEED 1

class VisualEntity {
	private:
		// Reference to the entity
		const Entity& _entity;

		// Texture
		Texture2D _texture;
		float sprite_width;
		float sprite_height;
		std::tuple<int, int> _sprite_dim;
		float _sprite_scale_mult;

		Vector2 _position = {0.0f, 0.0f};

		// Sprite frame
		Rectangle init_sprite_rect();
		Rectangle _frame_rec;
		float _frame_timer;

		// Movement
		float speed = 100.0f;
		float dx = 0;
		float dy = 0;

	protected:
		virtual void update_movement(float delta_time);

	public:
		VisualEntity(const Entity& entity, std::tuple<int, int> sprite_dim, float scale = 1.0f);

		virtual ~VisualEntity();

		// Protection against copying texture
		VisualEntity(const VisualEntity&) = delete;
		VisualEntity& operator=(const VisualEntity&) = delete;

		virtual void update(float delta_time);

		// Draw
		void on_draw();
		void unload_texture();

		// Position
		Vector2 getPos() const;
		bool setPos(Vector2 new_pos);
		void set_direction(float new_dx, float new_dy);

		// Error
		std::string sendObjectError(std::string error) const;
};
