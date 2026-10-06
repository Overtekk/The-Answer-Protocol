/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:56:53 by nbuchy            #+#    #+#             */
/*   Updated: 2026/10/06 11:44:23 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <unordered_map>
# include "Entity.hpp"
# include "config/Enums.hpp"


class NPC : public Entity {
    private :
		std::unordered_map<std::string, std::string> _dialogue;

    public :
        // Constructor
        NPC(
			const std::string& name, const std::string& description, const fs::path& sprite,
			std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
		);

        // Destructor
        ~NPC() = default;
};
