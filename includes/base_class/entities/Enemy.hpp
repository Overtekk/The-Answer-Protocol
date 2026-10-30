/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roandrie <roandrie@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 10:10:24 by roandrie          #+#    #+#             */
/*   Updated: 2026/10/27 09:55:10 by roandrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>

# include "Entity.hpp"
# include "config/Enums.hpp"


// * REPRESENT AN ENEMY *
class Enemy : public Entity {
	public :
		// --- CONSTRUCTOR ---
		Enemy(
			const std::string& id, const std::string& name, const std::string& description,
			EnemyType type, int health
		);
		// --- DESTRUCTOR ---
		~Enemy() override = default;
};
