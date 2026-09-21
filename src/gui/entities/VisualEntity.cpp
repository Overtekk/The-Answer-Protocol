/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualEntity.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:38:54 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/21 14:56:57 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/entities/VisualEntity.hpp"

VisualEntity::VisualEntity(
	const fs::path& sprite_path, std::tuple<int, int> sprite_dim, float scale
):
	_texture(LoadTexture(sprite_path.string().c_str())),
	_sprite_scale_mult(scale),
	_sprite_dim(sprite_dim) {}

VisualEntity::~VisualEntity() {
    UnloadTexture(_texture);
}

Rectangle VisualEntity::init_sprite_rect() {
    return {0.0f, 0.0f, (float)std::get<0>(_sprite_dim), (float)std::get<1>(_sprite_dim)};
}

void VisualEntity::on_draw(float x, float y) {
    Rectangle source = init_sprite_rect();
    Rectangle dest = {
        x, y, source.width * _sprite_scale_mult, source.height * _sprite_scale_mult
    };
    Vector2 origin = {0.0f, 0.0f};

    DrawTexturePro(_texture, source, dest, origin, 0.0f, WHITE);
}
