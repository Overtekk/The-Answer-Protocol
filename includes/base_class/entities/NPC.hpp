/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:56:53 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/09 09:13:04 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <unordered_map>

# include "Entity.hpp"
# include "config/Enums.hpp"


// * Represent a NPC *
class NPC : public Entity {
    private :
		std::unordered_map<std::string, std::string> _dialogue;

    public :
        // --- CONSTRUCTOR ---
        NPC(
			const std::string& name, const std::string& description,
			std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
		);
        // --- DESTRUCTOR ---
        ~NPC() override = default;
};
