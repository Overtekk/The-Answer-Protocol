/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ItemConsumable.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 10:35:34 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 09:16:59 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Item.hpp"
# include "config/Enums.hpp"


class ItemConsumable : public Item {
	public:
		// --- CONSTRUCTOR ---
		ItemConsumable(
			const std::string& name, const std::string& description, ItemType type,
			int damage, int hp);
		// --- DESTRUCTOR ---
		~ItemConsumable() override = default;
};
