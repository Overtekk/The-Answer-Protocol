/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ItemWeapon.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:07:21 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 13:14:12 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "base_class/items/ItemWeapon.hpp"


// --- CONSTRUCTOR ---
ItemWeapon::ItemWeapon(
	const std::string& id, const std::string& name, const std::string& description, ItemType type,
	int damage, int hp
):
	Item(id, name, description, type, damage, hp) {}
