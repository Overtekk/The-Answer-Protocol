/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualEntity.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:38:54 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/21 16:49:36 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui/entities/VisualEntity.hpp"

VisualEntity::VisualEntity(
	const Entity& entity, std::tuple<int, int> sprite_dim, float scale
):
	_entity(entity),
	LoadTexture(entity.getSpritePath().string().c_str()),
	_sprite_scale_mult(scale),
	_sprite_dim(sprite_dim) {}

VisualEntity::~VisualEntity() {
    UnloadTexture(_texture);
}

Rectangle VisualEntity::init_sprite_rect() {
    return {0.0f, 0.0f, (float)std::get<0>(_sprite_dim), (float)std::get<1>(_sprite_dim)};
}

void VisualEntity::on_draw() {
    Rectangle source = init_sprite_rect();
    Rectangle dest = {
        _entity.getPos, y, source.width * _sprite_scale_mult, source.height * _sprite_scale_mult
    };
    Vector2 origin = {0.0f, 0.0f};

    DrawTexturePro(_texture, source, dest, origin, 0.0f, WHITE);
}
