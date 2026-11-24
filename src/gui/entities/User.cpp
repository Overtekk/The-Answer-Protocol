/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 11:07:51 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/24 17:00:50 by nbuchy           ###   ########.fr       */
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

    int x = 0, y = 0;

    if (!_activeKeys.empty()) {
		// get the key from the top of the stack (end of the vector)
		int last = _activeKeys.back();

        switch (last) {
            case KEY_UP:  
			case KEY_W:  
				y = -1;
				break;
            case KEY_DOWN:
            case KEY_S:
				y = +1;
				break;
            case KEY_LEFT:
            case KEY_A:
				x = -1;
				break;
            case KEY_RIGHT:
            case KEY_D:
				x = +1;
				break;
        }
    }

    if (this->checkMapCollison(this->getPos().x + x, this->getPos().y + y) == true) {
        setDirection(0, 0);
    }
    else {
        setDirection(x, y);
    }
}

bool		User::checkMapCollison(float x, float y) {
    TmxLayer 	*object_layers = _room->getCurrentRoom()->getTileMap()->layers[3].layers; // we collect all the sub layer from the 3rd level
	int32_t		nb_layers = _room->getCurrentRoom()->getTileMap()->layers[3].layersLength; // how many sub layer we have
	int 		i = 0;

    // rectangle used for checking collison
    Rectangle   user_foot = Rectangle{
        x - float(this->getWidth()) / 2,
        y + float(this->getHeight()) / 2 - 3,
        float(this->getWidth()),
        3.0f
    };

	while (i < nb_layers) {
        // exact allows you to select the layer type, here it's objectGroup used by Tiled for collisons
        if (CheckCollisionTMXObjectGroupRec((object_layers + i)->exact.objectGroup, user_foot, nullptr) == 1) {
            return (true);
        }
		i++;
	}
    return (false);
}

void    User::giveRoomManager(RoomManager *room) {
    this->_room = room;
}
