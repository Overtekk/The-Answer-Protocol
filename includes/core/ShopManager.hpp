/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShopManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 09:13:09 by roandrie          #+#    #+#             */
/*   Updated: 2026/11/23 13:36:48 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "base_class/entities/NPCShop.hpp"
# include <string>


class ShopManager {
	private :

	public :
		// CONSTRUCTOR
		ShopManager();
		// DESTRUCTOR
		~ShopManager() = default;

		const std::string	formatNpcShopMap(NPCShop* entity) const;
};
