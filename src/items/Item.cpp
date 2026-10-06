/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Item.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:07:14 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 13:00:26 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "base_class/items/Item.hpp"

Item::Item(
	const std::string& name, const std::string& description, ItemType type,
	int damage, int hp
):
	_name(name),
	_description(description),
	_type(type),
	_damage(damage),
	_hp(hp),
	_id(_next_id++) {}

// --- GETTER ---
std::string Item::getName() const { return _name; }
ItemID Item::getId() const { return _id; }
std::string Item::getDescription() const { return _description; }
ItemType Item::getType() const { return _type; }
int Item::getDamage() const { return _damage; }
int Item::getHP() const { return _hp; }

// --- ERROR ---
std::string Item::sendObjectError(std::string error) const {
	std::ostringstream oss;
    oss << this << " object error: " << error << "\n";
    return oss.str();
}
