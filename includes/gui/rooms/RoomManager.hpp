/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:44:56 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/24 10:11:18 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma  once

# include <nlohmann/json.hpp>
# include <string>

# include "config/Enums.hpp"
# include "gui/rooms/VisualRoom.hpp"
# include "gui/data/VisualWorldState.hpp"
# include "gui/connection/ServerLink.hpp"
# include "gui/entities/User.hpp"
# include "gui/GameCamera.hpp"
# include "raylib.h"

using json = nlohmann::json;


class RoomManager
{
    private:
        VisualWorldState						&_data;
        ServerLink								&_link;

        User*									_user;
        VisualRoom*								_current_room;

		bool									_changing_room = false;
		Direction								_last_wrong_direction;
    public:
        RoomManager(
            VisualWorldState &data,
           	ServerLink &link,
			User *user
        );

        ~RoomManager() = default;

		// return opposit coordinate for the new room based on the new room size
		Vector2		getOppositCoordinates(Direction direction);
		
		// add all item returned by the look command to the current room
        void    	addItemsToRoom(const json &data);
		
		// get the look reply, call addItemsToRoom and set changing_room
		// variable to false when the current room is correctly updated
        bool    	updateRoomState();
        
		// Change current room, set the player coordinates to the opposite 
		// direction from the last room and set the changing_room
		// variable to false
		void		changeRoom(const std::string &room_id, Direction direction);
		
		// Update items (in the current room) state if the player picked it up
        void    	checkItemsPickedUp();
        
		// Update current room state
		void		updateRoom();
		// Draw current room
		void		drawRoom(GameCamera *camera);

		// Check if the player reached the limit of the current room and
		// init a room change if the server validate the move
		void		isPlayerOut();

		// Return a pointer to the current room
		VisualRoom	*getCurrentRoom();

        void		shutUp() { std::ignore = this->_user; std::ignore = this->_data; }
};

