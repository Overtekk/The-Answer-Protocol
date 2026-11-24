/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPCShop.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:56:53 by nbuchy            #+#    #+#             */
/*   Updated: 2026/11/20 12:16:05 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <unordered_map>

# include "NPC.hpp"
# include "config/Enums.hpp"


// * Represent a NPC with a shop *
class NPCShop : public NPC {
	private :
		std::unordered_map<std::string, int>	_stock;

	public :
		// --- CONSTRUCTOR ---
		NPCShop(
			const std::string& id, const std::string& name, const std::string& description,
			EnemyType type, int health
		);
		// --- DESTRUCTOR ---
		~NPCShop() override = default;

		const std::unordered_map<std::string, int>&	getShopList() const;

		void	addItemToShop(const std::string& item_id, int price);
		void	removeItemToShop(const std::string& item_id);
};
