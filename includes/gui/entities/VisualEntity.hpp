/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualEntity.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:31:16 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/21 14:57:36 by roandrie         ###   ########.fr       */
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
		Texture2D _texture;
		float _sprite_scale_mult;
		Rectangle _frame_rec;
		float sprite_width;
		float sprite_height;
		std::tuple<int, int> _sprite_dim;
		float _frame_timer;

		Rectangle init_sprite_rect();

	public:
		VisualEntity(const fs::path& sprite_path, std::tuple<int, int> sprite_dim, float scale = 1.0f);

		virtual ~VisualEntity();

		void on_draw(float x, float y);
		void unload_texture();
};
