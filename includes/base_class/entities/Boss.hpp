/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:13:24 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 11:44:04 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <unordered_map>
# include "Entity.hpp"
# include "config/Enums.hpp"


class Boss : public Entity {
    private :
		std::unordered_map<std::string, std::string> _dialogue;

    public :
        // Constructor
        Boss(
			const std::string& name, const std::string& description, const fs::path& sprite,
			std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
		);

        // Destructor
        ~Boss() = default;
};
