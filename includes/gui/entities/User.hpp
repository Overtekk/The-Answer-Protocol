/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:48:27 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/24 16:09:50 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include "gui/entities/VisualEntity.hpp"

// pre-definition of the class RoomManger, I need to do this to avoid circular
// dependences betwen RoomManager and User
class RoomManager;

class User : public VisualEntity {
	private:
		std::vector<int> 	_activeKeys;
		int 				_keys[8] = {KEY_UP, KEY_W ,KEY_DOWN, KEY_S ,KEY_LEFT, KEY_A ,KEY_RIGHT, KEY_D};
		
		RoomManager			*_room = nullptr;

		virtual void updateMovement() override;

	public:
		User(
			const std::string id,
			const Texture2D &texture,
			std::tuple<int, int> sprite_dim,
			float scale
		);

		// Check if the player collide with on of the Tile map Object, return true if collison else false
		bool		checkMapCollison(float x, float y);

		void		giveRoomManager(RoomManager *room);
};
