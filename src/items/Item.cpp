/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Item.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 14:07:14 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/02 15:45:15 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>

# include "base_class/items/Item.hpp"
# include "utils.h"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
Item::Item(
	const std::string& id, const std::string& name, const std::string& description, ItemType type,
	int damage, int hp, int bonus_min, int bonus_max
):
	_id(id),
	_name(name),
	_description(description),
	_type(type),
	_damage(damage),
	_hp(hp),
	_unique_id(_next_id++),
	_bonus_min(bonus_min),
	_bonus_max(bonus_max) {}

// ============================================================================
// =====================         GETTER      ==================================
// ============================================================================
const std::string&	Item::getName() const { return _name; }
const std::string&	Item::getID() const { return _id; }
ItemID				Item::getUniqueID() const { return _unique_id; }
const std::string&	Item::getDescription() const { return _description; }
ItemType			Item::getType() const { return _type; }
int					Item::getDamage() const { return _damage; }
int					Item::getHP() const { return _hp; }
int					Item::getBonusMin() { return _bonus_min; }
int 				Item::getBonusMax() { return _bonus_max; }

// ============================================================================
// =====================         ERROR       ==================================
// ============================================================================
void	Item::sendObjectError(const std::string& error) const {
	print_log(" ERROR: " + error + "\n");
}
