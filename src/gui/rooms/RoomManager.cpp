/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RoomManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchy <nbuchy@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 13:45:19 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/22 11:14:38 by nbuchy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	line = _link.look();
	if (line.empty()) { std::cout << "Waiting response\n"; return (false); }
	
	std::cout << "Data recived, parsing started\n";
	this->addItemsToRoom(json::parse(line.substr(3)));
	return (true);
}

void	RoomManager::changeRoom() {
	if (this->updateRoomState() == false) { return; }

	this->_changing = false;
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

	if (this->_changing == true) {
		this->changeRoom();
	}
	else if (this->_changing == false) {
		this->checkItemsPickedUp();
	}
}


void	RoomManager::isPlayerOut() {
	if (IsKeyReleased(KEY_N)) {
		std::cout << "player is leaving\n";
		this->_changing = true;
	}
}

void	RoomManager::drawRoom() {
	this->_current_room->drawItems();
}