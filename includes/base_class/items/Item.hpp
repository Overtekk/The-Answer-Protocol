/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Item.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 12:57:13 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/02 15:43:36 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <cstdint>

# include "config/Enums.hpp"

using ItemID = uint64_t;


// * ABSTRACT CLASS *
class Item {
	private :
	std::string	_id;
	std::string	_name;
	std::string	_description;
	ItemType 	_type;
	int 		_damage;
	int 		_hp;
	ItemID 		_unique_id;
	int			_bonus_min;
	int			_bonus_max;

	inline static ItemID _next_id = 1;

	public :
		// --- CONSTRUCTOR ----
		Item(
			const std::string& id, const std::string& name, const std::string& description,
			ItemType type, int damage, int hp, int bonus_min, int bonus_max);
		// --- DESTRUCTOR ---
		virtual ~Item() = default;

		// --- GETTER ---
		const std::string&	getName() const;
		const std::string&	getID() const;
		ItemID 				getUniqueID() const;
		const std::string&	getDescription() const;
		ItemType 			getType() const;
		int 				getDamage() const;
		int 				getHP() const;
		int					getBonusMin();
		int					getBonusMax();

		// Error
		void	sendObjectError(const std::string& error) const;
};

