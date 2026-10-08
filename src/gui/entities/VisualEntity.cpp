/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualEntity.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:38:54 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/08 12:12:38 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cmath>
# include "gui/entities/VisualEntity.hpp"
# include "utils.h"

# define FRAME_DURATION 0.18f

VisualEntity::VisualEntity(
	const Entity& entity, const std::string texture, std::tuple<int, int> sprite_dim, float scale
):
	_entity(entity),
	_img(LoadTexture(texture.c_str())),
	_sprite_dim(sprite_dim),
	_sprite_scale(scale),
	_idle(Animation(texture, sprite_dim, 4, 1, 0, FRAME_DURATION)),
	_walk_down(Animation(texture, sprite_dim, 4, 4, 0, FRAME_DURATION)),
	_walk_up(Animation(texture, sprite_dim, 4, 4, 8, FRAME_DURATION)),
	_walk_lr(Animation(texture, sprite_dim, 4, 4, 4, FRAME_DURATION))
	{
		if (this->_img.id == 0)
			this->sendObjectError("Error while loading texture");
		std::cout << this->_entity.getName() << " Created\n";
	}

VisualEntity::~VisualEntity() { UnloadTexture(this->_img); }

// Update
void VisualEntity::update(float delta_time) {
	update_movement(delta_time);
	// Normalize vector (unit vector when you go on )
	float length = sqrt((_dx * _dx) + (_dy * _dy));
	if (length > 0) {
		_dx = _dx / length;
		_dy = _dy / length;
	}

	if (_dy > 0) {
		_direction_row = EntityDirection::DOWN;
	}
	else if (_dy < 0) {
		_direction_row = EntityDirection::UP;
	}
	else if (_dx > 0) {
		_direction_row = EntityDirection::RIGHT;
	}
	else if (_dx < 0) {
		_direction_row = EntityDirection::LEFT;
	}

	update_sprite();

	_position.x += _dx * _speed * delta_time;
	_position.y += _dy * _speed * delta_time;
	// std::cout << delta_time << "\n";
	// std::cout << "x = " <<(_dx * _speed * delta_time) << "\n";
	// std::cout << "y = " <<(_dy * _speed * delta_time) << "\n\n";
	// _dx = 0.0f;
	// _dy = 0.0f;
};

void VisualEntity::update_movement(float) {}

// void VisualEntity::update_sprite(float delta_time) {
// 	if (_dx != 0.0f || _dy != 0.0f) {
// 		_frame_timer += delta_time;

// 		if (_frame_timer > FRAME_DURATION) {
// 			_frame_timer = 0;
// 			_current_frame = (_current_frame + 1) % 4;
// 		}
// 	}
// 	else {
// 		_frame_timer = 0;
// 		_current_frame = 0;
// 	}
// }

// Draw
// void VisualEntity::on_draw() {
//     Rectangle source = init_sprite_rect();
// 	auto [px, py] = getPos();
//     Rectangle dest = {
//         px, py, (std::abs(source.width) * _sprite_scale), source.height * _sprite_scale
//     };
//     Vector2 origin = {0.0f, 0.0f};
//     DrawTexturePro(_img, source, dest, origin, 0.0f, WHITE);
// }

void VisualEntity::update_sprite()
{
	if (_dx != 0.0f || _dy != 0.0f)
	{
		this->_walk_up.update_frame();
		this->_walk_down.update_frame();
		this->_walk_lr.update_frame();
	}
	else
	{
		this->_walk_up.reset();
		this->_walk_down.reset();
		this->_walk_lr.reset();
	}
}

void 	VisualEntity::on_draw()
{
	switch (this->_direction_row)
	{
	case EntityDirection::UP :
		this->_walk_up.draw_curent_frame(this->_position.x, this->_position.y, this->_sprite_scale);
		break;

	case EntityDirection::DOWN :
		this->_walk_down.draw_curent_frame(this->_position.x, this->_position.y, this->_sprite_scale);
		break;

	case EntityDirection::LEFT :
		this->_walk_lr.draw_curent_frame(this->_position.x, this->_position.y, this->_sprite_scale);
		break;

	case EntityDirection::RIGHT :
		this->_walk_lr.draw_curent_frame(this->_position.x, this->_position.y, this->_sprite_scale, true);
		break;

	default:
		this->_idle.draw_curent_frame(this->_position.x, this->_position.y, this->_sprite_scale);
		break;
	}
}

// Utils
// Rectangle VisualEntity::init_sprite_rect() {
// 	float x = _current_frame * (float)std::get<0>(_sprite_dim);
// 	float y = static_cast<int>(_direction_row) * (float)std::get<1>(_sprite_dim);
// 	if (_facing_left) {
//     	return {x, y, (float)std::get<0>(_sprite_dim), (float)std::get<1>(_sprite_dim)};
// 	}
// 	return {x, y, -(float)std::get<0>(_sprite_dim), (float)std::get<1>(_sprite_dim)};
// }

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
void VisualEntity::sendObjectError(std::string error) {
   print_log(" ERROR: " + error + "\n");
}
