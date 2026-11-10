/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ItemKey.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 10:35:34 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/02 15:46:12 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

# include "Item.hpp"
# include "config/Enums.hpp"


class ItemKey : public Item {
	public:
		// --- CONSTRUCTOR ---
		ItemKey(
			const std::string& id, const std::string& name, const std::string& description,
			ItemType type, int damage, int hp, int bonus_min, int bonus_max);
		// --- DESTRUCTOR ---
		~ItemKey() override = default;
};
