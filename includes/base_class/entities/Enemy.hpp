/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:10:24 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/06 13:02:47 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <unordered_map>
# include "Entity.hpp"
# include "config/Enums.hpp"

// * REPRESENT AN ENEMY *
class Enemy : public Entity {
    private :
		std::unordered_map<std::string, std::string> _dialogue;

    public :
        // --- CONSTRUCTOR ---
        Enemy(
			const std::string& name, const std::string& description, const fs::path& sprite,
			std::unordered_map<std::string, std::string> dialogue, EnemyType type, int health
		);
        // --- DESTRUCTOR ---
        ~Enemy() = default;
};
