/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualEntity.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:38:54 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/25 15:01:38 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cmath>
# include "gui/entities/VisualEntity.hpp"

# define FRAME_DURATION 0.18f

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
	float length = sqrt((_dx * _dx) + (_dy * _dy));
	if (length > 0) {
		_dx = _dx / length;
		_dy = _dy / length;
	}
	if (_dy > 0) {
		_direction_row = DOWN;
	}
	else if (_dy < 0) {
		_direction_row = UP;
	}
	else if (_dx != 0) {
		_direction_row = LEFT;
		if (_dx > 0) {
			_facing_left = false;
		}
		else {
			_facing_left = true;
		}
	}

	update_sprite(delta_time);

	_position.x += _dx * _speed * delta_time;
	_position.y += _dy * _speed * delta_time;
	_dx = 0.0f;
	_dy = 0.0f;
};

void VisualEntity::update_movement(float) {}

void VisualEntity::update_sprite(float delta_time) {
	if (_dx != 0.0f || _dy != 0.0f) {
		_frame_timer += delta_time;

		if (_frame_timer > FRAME_DURATION) {
			_frame_timer = 0;
			_current_frame = (_current_frame + 1) % 4;
		}
	}
	else {
		_frame_timer = 0;
		_current_frame = 0;
	}
}

// Draw
void VisualEntity::on_draw() {
    Rectangle source = init_sprite_rect();
	auto [px, py] = getPos();
    Rectangle dest = {
        px, py, (std::abs(source.width) * _sprite_scale_mult), source.height * _sprite_scale_mult
    };
    Vector2 origin = {0.0f, 0.0f};

    DrawTexturePro(_texture, source, dest, origin, 0.0f, WHITE);
}

// Utils
Rectangle VisualEntity::init_sprite_rect() {
	float x = _current_frame * (float)std::get<0>(_sprite_dim);
	float y = _direction_row * (float)std::get<1>(_sprite_dim);
	if (_facing_left) {
    	return {x, y, (float)std::get<0>(_sprite_dim), (float)std::get<1>(_sprite_dim)};
	}
	return {x, y, -(float)std::get<0>(_sprite_dim), (float)std::get<1>(_sprite_dim)};
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
	_dx = std::clamp(new_dx, -1.0f, 1.0f);
	_dy = std::clamp(new_dy, -1.0f, 1.0f);
}

// Error
std::string VisualEntity::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}
