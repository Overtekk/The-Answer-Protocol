/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:45:19 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/13 14:39:34 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
# include <cstdlib>
# include <csetjmp>
# include <iostream>
# include <raylib.h>
# include <string>
# include <nlohmann/json.hpp>

# include "gui.h"
# include "gui/rooms/RoomManager.hpp"
# include "gui/Items/VisualItem.hpp"
# include "gui/Items/VisualItemWeapon.hpp"
# include "gui/rooms/VisualRoom.hpp"
# include "gui/data/VisualWorldState.hpp"
# include "gui/connection/ServerLink.hpp"
# include "gui/entities/User.hpp"
#include "utils.h"

using json = nlohmann::json;

RoomManager::RoomManager(
    VisualWorldState &data,
    ServerLink &link,
	User *user
):
    _data(data),
    _link(link),
    _user(user),
	_current_room(data.getRoom("spawn"))
{}

void    RoomManager::addItemsToRoom(const json &data) {
	for (auto item_data : data.at("items")) {
		VisualItem	*item;
		if (item_data[1] == "weapon") {
			std::cout << "weapon item ";
			item = this->_data.getAddWeapon(item_data[0]);
		}
		else if (item_data[1] == "key") {
			std::cout << "key item ";	
			item = this->_data.getAddKey(item_data[0]);
		}
		else if (item_data[1] == "consumable") {
			std::cout << "consumable item ";
			item = this->_data.getAddConsumable(item_data[0]);
		}
		else {
			std::cout << "untyped item ";
			item = this->_data.getAddItem(item_data[0]);
		}

		item->setPos(Vector2 {(float)(rand() % 800), (float)(rand() % 450)});
		this->_current_room->addItem(item, item_data[0]);
	}
}

bool    RoomManager::updateRoomState() {
	std::string line = "";

	line = _link.getLookReply();
	if (line.empty()) {return(false) ;}
	
	std::cout << "Data recived, parsing started\n";
	std::cout << "DEBUG =[" << line << "]\n";
	this->addItemsToRoom(json::parse(line.substr(3)));
	return (true);
}

void	RoomManager::changeRoom(const std::string &room_id) {
	this->_current_room = this->_data.getRoom(room_id);

	std::cout << "Current location = [" << room_id << "]\n";
	this->_user->setPos(Vector2 {400, 225});

	this->_link.send_commande("LOOK --details", Commande::LOOK);
}

void    RoomManager::checkItemsPickedUp() {
	for (auto item_pair : this->_current_room->getItems()) {
		VisualItem	*item = item_pair.second;

		if (IsKeyReleased(KEY_E)) {
			if (checkCollison(
				_user->getPos().x, _user->getPos().y, _user->getWidth(), _user->getHeight(),
				item->getPos().x, item->getPos().y, item->getChestWidth(), item->getChestHeight()
			)) {
				item->ItemPicked();
			}
		}
	}
}

void	RoomManager::updateRoom() {
	this->isPlayerOut();

	this->updateRoomState();
	
	this->checkItemsPickedUp();
}


void	RoomManager::isPlayerOut() {
	std::string direction = "";
	std::string response = "";
	Vector2		user_pos = this->_user->getPos();

	if (user_pos.x <= 400.0 - (float)this->_current_room->getWidth() / 2) {
		direction = "west";
	}
	else if (user_pos.x >= 400.0 + (float)this->_current_room->getWidth() / 2) {
		direction = "east";
	}
	else if (user_pos.y <= 225.0 - (float)this->_current_room->getHeight() / 2) {
		direction = "north";
	}
	else if (user_pos.y >= 225.0 + (float)this->_current_room->getHeight() / 2) {
		direction = "south";
	}

	if (direction.empty() == true) {return ;}

	// get the respone
	response = this->_link.move(direction);
	if (response.empty() or response.find("ERR") == 0) {
		if (response.find("ERR") == 0) {std:: cout << "DEBUG, NO PATH THIS WAY\n"; }
		// std::cout << "Waiting response\n";
		return ;
	}
	size_t start_pos = response.find("=") + 1;
	size_t lenght = response.size() - start_pos;
	this->changeRoom(response.substr(start_pos, lenght));
}

void	RoomManager::drawRoom() {
	this->_current_room->drawItems();
}