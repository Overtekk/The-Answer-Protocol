/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPCShop.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:56:53 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/06 11:44:26 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <unordered_map>
# include "NPC.hpp"
# include "config/Enums.hpp"


class NPCShop : public NPC {
    private :
		std::unordered_map<std::string, std::string> _dialogue;

    public :
        // Constructor
        NPCShop(
			const std::string& name, const std::string& description, const fs::path& sprite,
			std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
		);

        // Destructor
        ~NPCShop() = default;
};
