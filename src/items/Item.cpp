/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Item.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:07:14 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/21 14:44:00 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/items/Item.hpp"

Item::Item(
	const std::string& name, const fs::path& sprite
):
	_name(name),
	_id(_next_id++),
	sprite(sprite) {}

// Getter

std::string Item::getName() const { return _name; }

ItemID Item::getId() const { return _id; }

std::string Item::getDescription() const { return _description; }

std::tuple<int, int> Item::getPos() const { return _position; }

 // Setter

bool Item::setName(std::string& new_name) {
	if (new_name.length() >= 3 && new_name.length() <= 20) {
		_name = new_name;
		return true;
	}
	sendObjectError("Can't modify name. Minimum 3 and maximum 20 characters.");
	return false;
}

bool Item::setDescription(std::string& new_desc) {
	if (new_desc.length() >= 1 && new_desc.length() <= 1000) {
		_description = new_desc;
		return true;
	}
	sendObjectError("Can't modify description. Minimum 1 and maximum 1000 characters.");
	return false;
}

bool Item::setPos(std::tuple<int, int> new_pos) {
	if (std::get<0>(new_pos) < 0 || std::get<1>(new_pos) < 0) {
		sendObjectError("Position can't be negative.");
		return false;
	}
	_position = new_pos;
	return true;
}

// Error
std::string Item::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}
