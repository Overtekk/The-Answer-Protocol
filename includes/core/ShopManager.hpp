/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShopManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 09:13:09 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/23 14:48:23 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <unordered_map>

# include "base_class/entities/NPCShop.hpp"
# include "base_class/entities/Player.hpp"
# include "config/WorldConfig.hpp"


class ShopManager {
	private :

	public :
		// CONSTRUCTOR
		ShopManager();
		// DESTRUCTOR
		~ShopManager() = default;

		const std::string	formatNpcShopMap(NPCShop* entity, const std::unordered_map<std::string, ItemConfig>& items) const;

		bool	doesHaveItem(NPCShop* entity, const std::string item_id);
		bool	doesPlayerHaveMoney(NPCShop* entity, Player* player, const std::string item_id);

		void	buyObject(NPCShop* entity, Player* player, const std::string item_id);
};
