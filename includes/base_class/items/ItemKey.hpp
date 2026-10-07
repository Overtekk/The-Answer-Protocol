/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ItemKey.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 10:35:34 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 13:14:18 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Item.hpp"
# include "config/Enums.hpp"

class ItemKey : public Item {
	public:
		// --- CONSTRUCTOR ---
		ItemKey(
			const std::string& name, const std::string& description, ItemType type,
			int damage, int hp);
		// --- DESTRUCTOR ---
		virtual ~ItemKey() = default;
};
