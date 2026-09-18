/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Item.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 12:57:13 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/18 15:36:48 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <iostream>
# include <algorithm>
# include <filesystem>
# include <tuple>

namespace fs = std::filesystem;

class Item {
	private :
	std::string _name;
	std::string _description = "";
	std::tuple<int, int> _position;

	public :
		// Constructor
		Item(const std::string& name, const fs::path& sprite)
        : _name(name), sprite(sprite) {}

		// Destructor
		virtual ~Item() = default;

		// Path to sprite
		fs::path sprite;

		// Name
		std::string getName() const;
		bool setName(std::string&);

		// Description
		std::string getDescription() const;
		bool setDescription(std::string&);

		// Position
		std::tuple<int, int> getPos() const;
		bool setPos(std::tuple<int, int>);

		// Error
		std::string sendObjectError(std::string) const;
};

// Getter

inline std::string Item::getName() const { return _name; }

inline std::string Item::getDescription() const { return _description; }

inline std::tuple<int, int> Item::getPos() const { return _position; }

 // Setter

inline bool Item::setName(std::string& new_name) {
	if (new_name.length() >= 3 && new_name.length() <= 20) {
		_name = new_name;
		return true;
	}
	sendObjectError("Can't modify name. Minimum 3 and maximum 20 characters.");
	return false;
}

inline bool Item::setDescription(std::string& new_desc) {
	if (new_desc.length() >= 1 && new_desc.length() <= 1000) {
		_description = new_desc;
		return true;
	}
	sendObjectError("Can't modify description. Minimum 1 and maximum 1000 characters.");
	return false;
}

inline bool Item::setPos(std::tuple<int, int> new_pos) {
	if (std::get<0>(new_pos) < 0 || std::get<0>(new_pos) < 0) {
		sendObjectError("Position can't be negative.");
		return false;
	}
	_position = new_pos;
	return true;
}

// Error
inline std::string Item::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}
