/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:44:56 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/22 10:54:41 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma  once

# include <nlohmann/json.hpp>

# include "gui/rooms/VisualRoom.hpp"
# include "gui/data/VisualWorldState.hpp"
# include "gui/connection/ServerLink.hpp"
# include "gui/entities/User.hpp"

using json = nlohmann::json;

class RoomManager
{
    private:
        VisualWorldState		&_data;
        ServerLink				&_link;

        User*					_user;
        VisualRoom*				_current_room;
		bool					_changing = false;
    public:
        RoomManager(
            VisualWorldState &data,
           	ServerLink &link,
			User *user
        );

        ~RoomManager() = default;

        void    addItemsToRoom(const json &data);
        bool    updateRoomState();
        
		void	changeRoom();
		
        void    checkItemsPickedUp();
        
		void	updateRoom();
		void	drawRoom();

		void	isPlayerOut();

        void	shutUp() { std::ignore = this->_user; std::ignore = this->_data; }
};

