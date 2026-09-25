/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualEntity.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:31:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/25 09:49:26 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <tuple>
#include "raylib.h"
#include "base_class/entities/Entity.hpp"

# define MAX_FRAME_SPEED 15
# define MIN_FRAME_SPEED 1

class VisualEntity {
	private:
		// Reference to the entity
		const Entity& _entity;

		Texture2D _texture;
		float _sprite_scale_mult;
		Rectangle _frame_rec;
		float sprite_width;
		float sprite_height;
		std::tuple<int, int> _sprite_dim;
		float _frame_timer;

		Rectangle init_sprite_rect();

	public:
		VisualEntity(const Entity& entity, std::tuple<int, int> sprite_dim, float scale = 1.0f);

		virtual ~VisualEntity();

		// Protection against copying texture
		VisualEntity(const VisualEntity&) = delete;
		VisualEntity& operator=(const VisualEntity&) = delete;

		void on_draw();
		void unload_texture();
};
