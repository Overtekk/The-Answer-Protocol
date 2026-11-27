/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:45:19 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/27 11:48:23 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
# include <cstdlib>
# include <csetjmp>
# include <iostream>
# include <raylib.h>
# include <string>
# include <nlohmann/json.hpp>

# include "gui/HUD/TextBoxs/TextBoxManager.hpp"
# include "gui/HUD/TextBoxs/WaitingTextBox.hpp"
# include "gui/GameCamera.hpp"
# include "gui/rooms/RoomManager.hpp"
# include "gui/Items/VisualItem.hpp"
# include "gui/rooms/VisualRoom.hpp"
# include "gui/data/VisualWorldState.hpp"
# include "gui/connection/ServerLink.hpp"
# include "gui/entities/User.hpp"
# include "config/Enums.hpp"
# include "utils.h"

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
{
	this->_last_wrong_direction = Direction::UNKNOWN;
}

Vector2			RoomManager::getOppositCoordinates(Direction direction) {
	Vector2 opposit_dir;

	if (direction == Direction::EAST) {
		opposit_dir.x = 10;
		opposit_dir.y = (this->_current_room->getHeight() - 10) / 2.0;
	}
	else if (direction == Direction::WEST) {
		opposit_dir.x = (this->_current_room->getWidth() - 10);;
		opposit_dir.y = (this->_current_room->getHeight() - 10) / 2.0;
	}
	else if (direction == Direction::NORTH) {
		opposit_dir.x = (this->_current_room->getWidth() - 10) / 2.0;;
		opposit_dir.y = (this->_current_room->getHeight() - 10);
	}
	else { // South
		opposit_dir.x = (this->_current_room->getWidth() - 10) / 2.0;;
		opposit_dir.y = 10;
	}
	return (opposit_dir);
}

void    		RoomManager::addItemsToRoom(const json &data) {
	Vector2	creation_position;
	this->_current_room->RemoveAllItems(); // remove all items

	for (auto item_data : data.at("items")) {
		VisualItem	*item;
		// Set a position for any new item created
		creation_position = Vector2 {(float)(rand() % 800), (float)(rand() % 450)};

		if (item_data[1] == "weapon") {
			std::cout << "weapon item ";
			item = this->_data.getAddWeapon(item_data[0], creation_position);
		}
		else if (item_data[1] == "key") {
			std::cout << "key item ";	
			item = this->_data.getAddKey(item_data[0], creation_position);
		}
		else if (item_data[1] == "consumable") {
			std::cout << "consumable item ";
			item = this->_data.getAddConsumable(item_data[0], creation_position);
		}
		else {
			std::cout << "untyped item ";
			item = this->_data.getAddItem(item_data[0], creation_position);
		}

		this->_current_room->addItem(item, item_data[0]);
	}
}

bool    		RoomManager::updateRoomState() {
	std::string line = "";

	line = _link.getLookReply();
	if (line.empty()) {return(false) ;}
	
	std::cout << "Data recived, parsing started\n";
	this->addItemsToRoom(json::parse(line.substr(3)));

	_changing_room = false;
	return (true);
}

void			RoomManager::changeRoom(const std::string &room_id, Direction direction) {
	this->_current_room = this->_data.getRoom(room_id);

	std::cout << "Current location = [" << room_id << "]\n";

	this->_user->setPos(this->getOppositCoordinates(direction));

	this->_link.send_commande("LOOK --details", Commande::LOOK);
}

void    		RoomManager::checkItemsPickedUp() {
	for (auto item_pair : this->_current_room->getItems()) {
		VisualItem	*item = item_pair.second;

		if (IsKeyReleased(KEY_E)) {
			if (CheckCollisionPointRec(this->_user->getPos(), item->getItemBox())) {
				item->ItemPicked();
				TextBoxManager::access().addTextBox<WaitingTextBox>("You found an item !");
			}
		}
	}
}

void			RoomManager::updateRoom() {
	this->isPlayerOut();

	if (_changing_room == true) {
		this->updateRoomState();
	}
	
	this->checkItemsPickedUp();
}


void			RoomManager::isPlayerOut() {
	Direction direction = Direction::UNKNOWN;
	std::string response = "";
	Vector2		user_pos = this->_user->getPos();

	// reminder that tile map origine is at 0,0
	if (user_pos.x <= 0) {
		direction = Direction::WEST;
	}
	else if (user_pos.x >= (float)this->_current_room->getWidth()) {
		direction = Direction::EAST;
	}
	else if (user_pos.y <= 0) {
		direction = Direction::NORTH;
	}
	else if (user_pos.y >= (float)this->_current_room->getHeight()) {
		direction = Direction::SOUTH;
	}

	// if the player doesn't change room or tries to pass
	// twice through the same wrong direction
	if (direction == Direction::UNKNOWN or direction == this->_last_wrong_direction) {return ;}

	// get the respone
	response = this->_link.move(direction_to_string(direction));
	if (response.empty()) {
		return ;
	}
	if (response.find("ERR") == 0) {
		std:: cout << "DEBUG, NO PATH THIS WAY\n"; 
		_last_wrong_direction = direction;
		return;
	}

	_changing_room = true;
	size_t start_pos = response.find("=") + 1;
	size_t lenght = response.size() - start_pos;
	this->changeRoom(response.substr(start_pos, lenght), direction);
	_last_wrong_direction = Direction::UNKNOWN;
}

VisualRoom		*RoomManager::getCurrentRoom() {
	return (this->_current_room);
}

void			RoomManager::drawRoom(GameCamera *camera) {
	if (this->_changing_room == false){
		// Draw tile map
		DrawTMX(_current_room->getTileMap(), camera->getCamera(), NULL, 0, 0, WHITE);

		this->_current_room->drawItems();
	}
}
