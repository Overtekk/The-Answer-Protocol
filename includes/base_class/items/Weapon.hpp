/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 10:35:34 by roandrie          #+#    #+#             */
/*   Updated: 2026/09/19 10:42:06 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Item.hpp"

class Weapon : public Item {
	public:
		Weapon(const std::string& name, const fs::path& sprite)
        : Item(name, sprite) {}

};
