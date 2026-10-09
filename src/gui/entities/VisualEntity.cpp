/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VisualEntity.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:38:54 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 15:15:59 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cmath>
# include "gui/entities/VisualEntity.hpp"
# include "utils.h"

# define FRAME_DURATION 0.18f

VisualEntity::VisualEntity(
	const Entity& entity, const std::string &texture, std::tuple<int, int> sprite_dim, float scale
):
	_entity(entity),
	_img(LoadTexture(texture.c_str())),
	_sprite_dim(sprite_dim),
	_sprite_scale(scale),
	_idle(Animation(this->_img, sprite_dim, 4, 1, 0, FRAME_DURATION)),
	_walk_down(Animation(this->_img, sprite_dim, 4, 4, 0, FRAME_DURATION)),
	_walk_up(Animation(this->_img, sprite_dim, 4, 4, 8, FRAME_DURATION)),
	_walk_lr(Animation(this->_img, sprite_dim, 4, 4, 4, FRAME_DURATION))
	{
		if (this->_img.id == 0)
			this->sendObjectError("Error while loading texture");
		std::cout << this->_entity.getName() << " Created\n";
	}

VisualEntity::~VisualEntity() { UnloadTexture(this->_img); }

// Update
void VisualEntity::update() {
	float	delta_time = GetFrameTime();

	updateMovement();

	// Normalize vector (unit vector when you go on diagonal)
	// Wait, you can't go on diagonal ?!
	float length = sqrt((_dx * _dx) + (_dy * _dy));
	if (length > 0) {
		_dx = _dx / length;
		_dy = _dy / length;
	}

	if (_dy > 0) {
		_orientation = EntityDirection::DOWN;
	}
	else if (_dy < 0) {
		_orientation = EntityDirection::UP;
	}
	else if (_dx > 0) {
		_orientation = EntityDirection::RIGHT;
	}
	else if (_dx < 0) {
		_orientation = EntityDirection::LEFT;
	}

	updateSprite();

	_position.x += _dx * _speed * delta_time;
	_position.y += _dy * _speed * delta_time;
	// std::cout << delta_time << "\n";
	// std::cout << "x = " <<(_dx * _speed * delta_time) << "\n";
	// std::cout << "y = " <<(_dy * _speed * delta_time) << "\n\n";
};

void VisualEntity::updateMovement() {}

void VisualEntity::updateSprite()
{
	if (_dx != 0.0f || _dy != 0.0f)
	{
		this->_walk_up.updateFrame();
		this->_walk_down.updateFrame();
		this->_walk_lr.updateFrame();
	}
	else
	{
		this->_walk_up.reset();
		this->_walk_down.reset();
		this->_walk_lr.reset();
	}
}

void 	VisualEntity::onDraw()
{
	switch (this->_orientation)
	{
	case EntityDirection::UP :
		this->_walk_up.drawCurentFrame(this->_position.x, this->_position.y,
			this->_sprite_scale);
		break;

	case EntityDirection::DOWN :
		this->_walk_down.drawCurentFrame(this->_position.x, this->_position.y,
			this->_sprite_scale);
		break;

	case EntityDirection::LEFT :
		this->_walk_lr.drawCurentFrame(this->_position.x, this->_position.y,
			this->_sprite_scale);
		break;

	case EntityDirection::RIGHT :
		this->_walk_lr.drawCurentFrame(this->_position.x, this->_position.y,
			this->_sprite_scale, true); // flip the sprite
		break;

	default:
		this->_idle.drawCurentFrame(this->_position.x, this->_position.y,
			this->_sprite_scale);
		break;
	}
}

// Getter
const Vector2 &VisualEntity::getPos() const { return _position; }

EntityDirection VisualEntity::getOrientation() const { return(_orientation); }

// Setter
void VisualEntity::setPos(const Vector2 &new_pos) {
	_position = new_pos;
}

void VisualEntity::setOrientation(EntityDirection orientation)
{
	this->_orientation = orientation;
};

void VisualEntity::setDirection(float new_dx, float new_dy) {
	_dx = std::clamp(new_dx, -1.0f, 1.0f);
	_dy = std::clamp(new_dy, -1.0f, 1.0f);
}

// Error
void VisualEntity::sendObjectError(const std::string &error) {
   print_log(" ERROR: " + error + "\n");
}
