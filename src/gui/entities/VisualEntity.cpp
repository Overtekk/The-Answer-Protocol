/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualEntity.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:38:54 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/25 11:49:42 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cmath>
# include "gui/entities/VisualEntity.hpp"

VisualEntity::VisualEntity(
	const Entity& entity, std::tuple<int, int> sprite_dim, float scale
):
	_entity(entity),
	_texture(LoadTexture(entity.getSpritePath().string().c_str())),
	_sprite_dim(sprite_dim),
	_sprite_scale_mult(scale) {}

VisualEntity::~VisualEntity() { UnloadTexture(_texture); }

// Update
void VisualEntity::update(float delta_time) {
	update_movement(delta_time);
	// Normalize vector
	float length = sqrt((dx * dx) + (dy * dy));
	if (length > 0) {
		dx = dx / length;
		dy = dy / length;
	}

	_position.x += dx * speed * delta_time;
	_position.y += dy * speed * delta_time;
	dx = 0.0f;
	dy = 0.0f;
};

void VisualEntity::update_movement(float) { }

// Draw
void VisualEntity::on_draw() {
    Rectangle source = init_sprite_rect();
	auto [px, py] = getPos();
    Rectangle dest = {
        px, py, source.width * _sprite_scale_mult, source.height * _sprite_scale_mult
    };
    Vector2 origin = {0.0f, 0.0f};

    DrawTexturePro(_texture, source, dest, origin, 0.0f, WHITE);
}

// Utils
Rectangle VisualEntity::init_sprite_rect() {
    return {0.0f, 0.0f, (float)std::get<0>(_sprite_dim), (float)std::get<1>(_sprite_dim)};
}

// Getter
Vector2 VisualEntity::getPos() const { return _position; }

// Setter
bool VisualEntity::setPos(Vector2 new_pos) {
	if (new_pos.x < 0 || new_pos.y < 0) {
		sendObjectError("Position can't be negative.");
		return false;
	}
	_position = new_pos;
	return true;
}

void VisualEntity::set_direction(float new_dx, float new_dy) {
	dx = std::clamp(new_dx, -1.0f, 1.0f);
	dy = std::clamp(new_dy, -1.0f, 1.0f);
}

// Error
std::string VisualEntity::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}
