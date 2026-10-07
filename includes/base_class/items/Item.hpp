/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Item.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 12:57:13 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 14:13:57 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <algorithm>
# include <filesystem>
# include <tuple>
# include "config/Enums.hpp"

namespace fs = std::filesystem;
using ItemID = uint64_t;

// * ABSTRACT CLASS *
class Item {
	private :
	std::string	_name;
	std::string	_description;
	ItemType 	_type;
	int 		_damage;
	int 		_hp;
	ItemID 		_id;

	inline static ItemID _next_id = 1;

	public :
		// --- CONSTRUCTOR ----
		Item(
			const std::string& name, const std::string& description, ItemType type,
			int damage, int hp);
		// --- DESTRUCTOR ---
		virtual ~Item() = default;

		// --- GETTER ---
		std::string getName() const;
		ItemID 		getID() const;
		std::string getDescription() const;
		ItemType 	getType() const;
		int 		getDamage() const;
		int 		getHP() const;

		// Error
		std::string sendObjectError(std::string error) const;
};

