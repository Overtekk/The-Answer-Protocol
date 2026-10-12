/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Item.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:07:14 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/09 13:08:23 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "base_class/items/Item.hpp"
# include "utils.h"


Item::Item(
	const std::string& id, const std::string& name, const std::string& description, ItemType type,
	int damage, int hp
):
	_id(id),
	_name(name),
	_description(description),
	_type(type),
	_damage(damage),
	_hp(hp),
	_unique_id(_next_id++) {}

// --- GETTER ---
const std::string&	Item::getName() const { return _name; }
const std::string&	Item::getID() const { return _id; }
ItemID				Item::getUniqueID() const { return _unique_id; }
const std::string&	Item::getDescription() const { return _description; }
ItemType			Item::getType() const { return _type; }
int					Item::getDamage() const { return _damage; }
int					Item::getHP() const { return _hp; }

// --- ERROR ---
void	Item::sendObjectError(const std::string& error) const {
	print_log(" ERROR: " + error + "\n");
}
