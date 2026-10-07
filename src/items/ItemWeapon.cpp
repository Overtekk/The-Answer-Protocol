/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ItemWeapon.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:07:21 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 12:22:55 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/items/ItemWeapon.hpp"

// --- CONSTRUCTOR ---
ItemWeapon::ItemWeapon(
	const std::string& name, const std::string& description, ItemType type,
	int damage, int hp
):
	Item(name, description, type, damage, hp) {}
