/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPCShop.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:56:53 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/27 09:56:02 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

# include "NPC.hpp"
# include "config/Enums.hpp"


// * Represent a NPC with a shop *
class NPCShop : public NPC {
	public :
		// --- CONSTRUCTOR ---
		NPCShop(
			const std::string& id, const std::string& name, const std::string& description,
			EnemyType type, int health
		);
		// --- DESTRUCTOR ---
		~NPCShop() override = default;
};
