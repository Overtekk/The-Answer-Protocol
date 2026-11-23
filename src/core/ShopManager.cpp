/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShopManager.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 09:12:21 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/23 13:36:53 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <string>
# include <unordered_map>

# include "core/ShopManager.hpp"

// ============================================================================
// =====================       CONSTRUCTOR      ===============================
// ============================================================================
ShopManager::ShopManager() {}


// ============================================================================
// ====================       PUBLIC METHODS      =============================
// ============================================================================
const std::string	ShopManager::formatNpcShopMap(NPCShop* entity) const {
	std::string result = "";

	std::unordered_map<std::string, int> stock_list = entity->getShopList();

	for (const auto& [item_id, price] : stock_list) {
		result += "[\"" + item_id + "\"" + ": " + std::to_string(price) + "$] | ";
	}

	result.pop_back();
	result.pop_back();
	result.pop_back();
	return result;
}
