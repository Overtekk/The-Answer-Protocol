/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:48:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/25 11:51:39 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include "gui/entities/VisualEntity.hpp"
#include "raylib.h"

// pre-definition of the class RoomManger, I need to do this to avoid circular
// dependences betwen RoomManager and User
class RoomManager;

class User : public VisualEntity {
	private:
		std::vector<int> 	_activeKeys;
		int 				_keys[8] = {KEY_UP, KEY_W ,KEY_DOWN, KEY_S ,KEY_LEFT, KEY_A ,KEY_RIGHT, KEY_D};
		
		RoomManager			*_room = nullptr;

		// update direction (dx and dy) depending on keyboard inputs
		virtual void updateMovement() override;

	public:
		User(
			const std::string id,
			const Texture2D &texture,
			std::tuple<int, int> sprite_dim,
			float scale
		);
		
		// Update user position, orientation, and sprite
		virtual void update() override;

		// Check if the player collide with on of the Tile map Object, return true if collision else false
		bool		checkMapCollision(Rectangle &user_foot);
		// Check if the player go out the map, return true if he is out else false
		bool		checkOutOfMap(float x, float y);
		// Check if the player collide with an item on the current room, return true if collsision else false
		bool		checkItemCollision(Rectangle &user_foot);
		// Check for map layer collisions, items and out of map, return true if any type of collisions happen, else false
		bool		checkCollsions(float x, float y);

		// Dependency injection
		void		giveRoomManager(RoomManager *room);

		void		draw_foot();
};
