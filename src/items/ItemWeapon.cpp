/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ItemWeapon.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:07:21 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/02 15:44:12 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "base_class/items/ItemWeapon.hpp"
#include "base_class/items/Item.hpp"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
ItemWeapon::ItemWeapon(
	const std::string& id, const std::string& name, const std::string& description, ItemType type,
	int damage, int hp, int bonus_min, int bonus_max
):
	Item(id, name, description, type, damage, hp, bonus_min, bonus_max) {}


