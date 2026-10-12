/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPCShop.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:56:53 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/09 11:56:56 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <unordered_map>

# include "NPC.hpp"
# include "config/Enums.hpp"


// * Represent a NPC with a shop *
class NPCShop : public NPC {
    private :
		std::unordered_map<std::string, std::string> _dialogue;

    public :
        // --- CONSTRUCTOR ---
        NPCShop(
			const std::string& id, const std::string& name, const std::string& description,
			std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
		);
        // --- DESTRUCTOR ---
        ~NPCShop() override = default;
};
