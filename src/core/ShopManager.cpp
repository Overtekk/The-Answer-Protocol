/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShopManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 09:12:21 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/23 14:48:18 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include <unordered_map>

# include "core/ShopManager.hpp"
# include "config/WorldConfig.hpp"
# include "utils.h"


// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
ShopManager::ShopManager() {}


// ============================================================================
// ====================       PUBLIC METHODS      =============================
// ============================================================================
const std::string	ShopManager::formatNpcShopMap(NPCShop* entity, const std::unordered_map<std::string, ItemConfig>& items) const {
	std::string result = "";

	std::unordered_map<std::string, int> stock_list = entity->getShopList();

	for (const auto& [item_id, price] : stock_list) {
		const auto& it = items.find(item_id);
		if (it == items.end())
			continue;

		result += "[\"" + item_id + "\"(" + item_type_to_string(it->second.type) + "): " + std::to_string(price) + "$] | ";
	}

	result.pop_back();
	result.pop_back();
	result.pop_back();
	return result;
}


bool	ShopManager::doesHaveItem(NPCShop *entity, const std::string item_id) {
	return entity->getShopList().find(item_id) != entity->getShopList().end();
}


bool	ShopManager::doesPlayerHaveMoney(NPCShop *entity, Player *player, const std::string item_id) {
	if (doesHaveItem(entity, item_id)) {
		std::unordered_map<std::string, int> stock_list = entity->getShopList();

		int price = stock_list[item_id];

		if (player->getMoney() >= price)
			return true;
	}

	return false;
}


void	ShopManager::buyObject(NPCShop *entity, Player *player, const std::string item_id) {
	if (doesHaveItem(entity, item_id) && doesPlayerHaveMoney(entity, player, item_id)) {
		std::unordered_map<std::string, int> stock_list = entity->getShopList();

		int price = stock_list[item_id];

		player->setMoney(player->getMoney() - price);
		if (player->getMoney() < 0)
			player->setMoney(0);
	}
}
