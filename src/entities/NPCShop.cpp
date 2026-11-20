/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPCShop.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:04:23 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/20 12:21:27 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include <unordered_map>

# include "base_class/entities/NPCShop.hpp"
# include "config/config_messages.h"
# include "utils.h"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
NPCShop::NPCShop(
    const std::string& id, const std::string& name, const std::string& description, EnemyType type, int health):
	NPC(id, name, description, type, health) {}


// ============================================================================
// =====================          PUBLIC      =================================
// ============================================================================
const std::unordered_map<std::string, int>&	NPCShop::getShopList() const { return _stock; }

void	NPCShop::addItemToShop(const std::string& item_id, int price) { _stock[item_id] = price; }

void	NPCShop::removeItemToShop(const std::string& item_id) {
	if (_stock.find(item_id) == _stock.end()) {
		print_log(errShopItemRemove(getName(), item_id));
		return;
	}

	_stock.erase(item_id);
}
