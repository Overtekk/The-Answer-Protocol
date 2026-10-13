/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ItemWeapon.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 10:35:34 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 12:58:00 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Item.hpp"
# include "config/Enums.hpp"


class ItemWeapon : public Item {
	public:
		// --- CONSTRUCTOR ---
		ItemWeapon(
			const std::string& id, const std::string& name, const std::string& description,
			ItemType type, int damage, int hp);
		// --- DESTRUCTOR ---
		~ItemWeapon() override = default;
};
