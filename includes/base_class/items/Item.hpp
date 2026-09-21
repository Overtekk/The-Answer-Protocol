/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Item.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 12:57:13 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/21 14:43:26 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <iostream>
# include <algorithm>
# include <filesystem>
# include <tuple>

namespace fs = std::filesystem;
using ItemID = uint64_t;

class Item {
	private :
	std::string _name;
	ItemID _id;
	std::string _description = "";
	std::tuple<int, int> _position;

	inline static ItemID _next_id = 1;

	public :
		// Constructor
		Item(const std::string& name, const fs::path& sprite);

		// Destructor
		virtual ~Item() = default;

		// Path to sprite
		fs::path sprite;

		// Name
		std::string getName() const;
		bool setName(std::string& new_name);

		// ID
		ItemID getId() const;

		// Description
		std::string getDescription() const;
		bool setDescription(std::string& new_desc);

		// Position
		std::tuple<int, int> getPos() const;
		bool setPos(std::tuple<int, int> new_pos);

		// Error
		std::string sendObjectError(std::string error) const;
};

