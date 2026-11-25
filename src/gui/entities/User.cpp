/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 11:07:51 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/25 13:41:41 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <bits/stdc++.h>
# include <vector>
# include "gui/entities/User.hpp"
# include "gui/rooms/RoomManager.hpp"
# include "raylib.h"
#include "raytmx.h"

User::User(
			const std::string id,
			const Texture2D &texture,
			std::tuple<int, int> sprite_dim,
			float scale
) : VisualEntity(id, texture, sprite_dim, scale) {}

void User::updateMovement()
{
// listen for keys pressed
    for (int k : _keys) {
		// add the key to the stack if it's not already in stack
        if (IsKeyPressed(k) && std::count(_activeKeys.begin(), _activeKeys.end(), k) <= 0) {
            _activeKeys.push_back(k); // add it to the end
        }
    }

    // listen for keys released
    for (int k : _keys) {
		// remove the key from the stack
        if (IsKeyReleased(k) && std::count(_activeKeys.begin(), _activeKeys.end(), k) > 0) {
			// weird way to remove element (vector is ass)
            _activeKeys.erase(std::remove(_activeKeys.begin(), _activeKeys.end(), k), _activeKeys.end());
        }
    }

    float x = 0.0f, y = 0.0f;

    if (!_activeKeys.empty()) {
		// get the key from the top of the stack (end of the vector)
		int last = _activeKeys.back();

        switch (last) {
            case KEY_UP:  
			case KEY_W:  
				y = -1.0f;
				break;
            case KEY_DOWN:
            case KEY_S:
				y = +1.0f;
				break;
            case KEY_LEFT:
            case KEY_A:
				x = -1.0f;
				break;
            case KEY_RIGHT:
            case KEY_D:
				x = +1.0f;
				break;
        }
    }

    setDirection(x, y);
}

void User::update() {
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

    float new_x = _position.x + (_dx * _speed * delta_time);
    float new_y = _position.y + (_dy * _speed * delta_time);

    if (checkCollsions(new_x, new_y) == false) {
        updateSprite();
        _position.x = new_x;
        _position.y = new_y;
    }
};

bool		User::checkMapCollision(Rectangle &user_foot) {
    TmxLayer 	*object_layers = _room->getCurrentRoom()->getTileMap()->layers[3].layers; // we collect all the sub layer from the 3rd level
	int32_t		nb_layers = _room->getCurrentRoom()->getTileMap()->layers[3].layersLength; // how many sub layer we have
	int 		i = 0;

	while (i < nb_layers) {
        // exact allows you to select the layer type, here it's objectGroup used by Tiled for collisons
        if (CheckCollisionTMXObjectGroupRec((object_layers + i)->exact.objectGroup, user_foot, nullptr) == 1) {
            return (true);
        }
		i++;
	}
    return (false);
}

bool		User::checkOutOfMap(float x, float y) {
    (void)y;
    if (x < - 2 or x > this->_room->getCurrentRoom()->getWidth() + 2 or
        y < - 2 or y > this->_room->getCurrentRoom()->getHeight() + 2) {
        return (true);
    }
    return (false);
}

bool		User::checkItemCollision(Rectangle &user_foot) {
    for (auto item: this->_room->getCurrentRoom()->getItems()) {
        if (CheckCollisionRecs(user_foot, item.second->getItemBox())) {
            return (true);
        };
    }
    return (false);
}

bool		User::checkCollsions(float x, float y) {
    // rectangle used for checking map collison
    Rectangle   user_foot = Rectangle{
        x - float(this->getWidth()) / 2,
        y + float(this->getHeight()) / 2 - 3,
        float(this->getWidth()),
        3.0f
    };
    return (checkMapCollision(user_foot) or checkOutOfMap(x, y) or checkItemCollision(user_foot));
}

void    User::giveRoomManager(RoomManager *room) {
    this->_room = room;
}

void    User::draw_foot() {
    Rectangle   user_foot = Rectangle{
        getPos().x - float(this->getWidth()) / 2,
        getPos().y + float(this->getHeight()) / 2 - 3,
        float(this->getWidth()),
        3.0f
    };

    DrawRectangleRec(user_foot, RED);
}